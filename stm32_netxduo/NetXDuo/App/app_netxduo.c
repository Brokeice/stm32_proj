/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_netxduo.c
  * @author  MCD Application Team
  * @brief   NetXDuo applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_netxduo.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nx_stm32_eth_config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

UCHAR data_buffer[4096];

TX_THREAD AppTCPThread;

NX_PACKET_POOL AppPool;

ULONG IpAddress;
ULONG NetMask;
NX_IP IpInstance;

NX_DHCP DHCPClient;
NX_TCP_SOCKET TCPSocket;

UCHAR *pointer;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define  MAX_TCP_CLIENTS                1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static VOID App_TCP_Thread_Entry(ULONG thread_input);

/* USER CODE END PFP */
/**
  * @brief  Application NetXDuo Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_NetXDuo_Init(VOID *memory_ptr)
{
  UINT ret = NX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN MX_NetXDuo_MEM_POOL */
  (void)byte_pool;
  /* USER CODE END MX_NetXDuo_MEM_POOL */

  /* USER CODE BEGIN MX_NetXDuo_Init */
  printf("Nx_TCP_Echo_Client \r\n");

  nx_system_initialize();

  /* Allocate the memory for packet_pool.  */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,  NX_PACKET_POOL_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the Packet pool to be used for packet allocation */
  ret = nx_packet_pool_create(&AppPool, "Main Packet Pool", PAYLOAD_SIZE, pointer, NX_PACKET_POOL_SIZE);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }

  /* Allocate the memory for Ip_Instance */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,   2 * DEFAULT_MEMORY_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the main NX_IP instance */
  ret = nx_ip_create(&IpInstance, "Main Ip instance", TCP_SERVER_ADDRESS, 0xFFFFFF00UL, &AppPool,nx_stm32_eth_driver,
                     pointer, 2 * DEFAULT_MEMORY_SIZE, DEFAULT_PRIORITY);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }

  /* Allocate the memory for ARP */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, DEFAULT_MEMORY_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /*  Enable the ARP protocol and provide the ARP cache size for the IP instance */
  ret = nx_arp_enable(&IpInstance, (VOID *)pointer, DEFAULT_MEMORY_SIZE);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }

  /* 使能fragment */    
  ret = nx_ip_fragment_enable(&IpInstance);
  if (ret != NX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }

  /* Enable the ICMP */
  ret = nx_icmp_enable(&IpInstance);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }

  /* Enable the UDP protocol required for  DHCP communication */
  ret = nx_udp_enable(&IpInstance);

  /* Enable the TCP protocol */
  ret = nx_tcp_enable(&IpInstance);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }

  /* Allocate the memory for TCP server thread   */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,2 *  DEFAULT_MEMORY_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* create the TCP server thread */
  ret = tx_thread_create(&AppTCPThread, "App TCP Thread", App_TCP_Thread_Entry, 0, pointer, 2 * DEFAULT_MEMORY_SIZE,
                         DEFAULT_PRIORITY, DEFAULT_PRIORITY, TX_NO_TIME_SLICE, TX_AUTO_START);

  if (ret != TX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }



  return ret;
}

/**
* @brief  TCP thread entry.
* @param thread_input: thread user data
* @retval none
*/

static VOID App_TCP_Thread_Entry(ULONG thread_input)
{
  UINT ret;
  ULONG socket_state;
  ULONG bytes_read;
  

  ULONG peer_ip_address;
  ULONG peer_port;

  NX_PACKET *data_packet;

  /* create the TCP socket */
  ret = nx_tcp_socket_create(&IpInstance, &TCPSocket, "TCP Server Socket", NX_IP_NORMAL, NX_FRAGMENT_OKAY,
                             NX_IP_TIME_TO_LIVE, WINDOW_SIZE, NX_NULL, NX_NULL);
  if (ret != NX_SUCCESS)
  {
    printf("socket create failed\r\n");  
    Error_Handler();
  }

  /*
    * 监听新的链接。
    * 创建回调TCP_listen_callback表示监听到新连接。
    */
    ret = nx_tcp_server_socket_listen(&IpInstance,                  /* IP实例控制块 */  
									  DEFAULT_PORT,           /* 默认端口 */          
	                                  &TCPSocket,             /* TCP Socket控制块 */
	                                  MAX_TCP_CLIENTS,        /* 可以监听的连接数 */
	                                  NULL);   				  /* 监听回调函数 */

    if (ret)
    {
        printf("listen failed!\r\n");
    }

	/* 启动TCP通信前，接收新连接 */
	ret = nx_tcp_server_socket_accept(&TCPSocket,         /* TCP Socket控制块 */
	                                   TX_WAIT_FOREVER);  /* 监听回调函数 */

	if (ret)
	{
		printf("accept failed!\r\n");
	}

  while (1)
  {
    TX_MEMSET(data_buffer, '\0', sizeof(data_buffer));

    /* 获取socket状态 */
    nx_tcp_socket_info_get(&TCPSocket,    /* TCP Socket控制块 */
                           NULL,          /* 发送的TCP数据包总数目 */
                           NULL,          /* 发送的TCP总字节数 */
                           NULL,          /* 接收TCP数据包总数目 */
                           NULL,          /* 接收的TCP总字节数 */
                           NULL,          /* 重新传输的TCP数据包总数目 */
                           NULL,          /* Socket上TCP排队的TCP数据包总数 */
                           NULL,          /* Socket上有校验和错误的TCP数据包总数 */
                           &socket_state, /* Socket当前状态 */
                           NULL,          /* 仍在排队等待ACK的发送数据包总数 */
                           NULL,          /* 当前发送窗口大小 */
                           NULL);         /* 当前接收窗口大小 */

    /* 如果连接还没有建立，继续接受新连接，成功的话开启接收数据 */
    if (socket_state != NX_TCP_ESTABLISHED)
    {
      /* 启动TCP通信前，接收新连接 */
      ret = nx_tcp_server_socket_accept(&TCPSocket,       /* TCP Socket控制块 */
                                        TX_WAIT_FOREVER); /* 等待连接 */

      if (ret)
      {
        printf("accept failed!\r\n");
      }
    }

    if ((socket_state == NX_TCP_ESTABLISHED) && (ret == NX_SUCCESS))
    {

      /* 接收TCP客户端发的TCP数据包 */
      ret = nx_tcp_socket_receive(&TCPSocket,       /* TCP Socket控制块 */
                                  &data_packet,     /* 接收到的数据包 */
                                  NX_WAIT_FOREVER); /* 永久等待 */

      if (ret == NX_SUCCESS)
      {

        /* 获取客户端的IP地址和端口 */
        nx_tcp_socket_peer_info_get(&TCPSocket,       /* TCP Socket控制块 */
                                    &peer_ip_address, /* 远程IP地址 */
                                    &peer_port);      /* 远程端口号 */

        /* 获取客户端发来的数据 */
        nx_packet_data_retrieve(data_packet,  /* 接收到的数据包 */
                                data_buffer,  /* 解析出数据 */
                                &bytes_read); /* 数据大小 */

        /* 打印接收到数据 */
        PRINT_DATA(peer_ip_address, (unsigned int)peer_port, data_buffer);

        /* 立即将接收到的数据发送回去 */
        ret = nx_tcp_socket_send(&TCPSocket,       /* TCP Socket控制块 */
                                 data_packet,      /* 数据包 */
                                 NX_WAIT_FOREVER); /* 永久等待 */
      }
      else
      {
        /* 断开连接 */
        nx_tcp_socket_disconnect(&TCPSocket,
                                 NX_WAIT_FOREVER);

        /* 解除Socket和服务器端口的绑定 */
        nx_tcp_server_socket_unaccept(&TCPSocket);

        /* 重新监听 */
        nx_tcp_server_socket_relisten(&IpInstance,
                                      DEFAULT_PORT,
                                      &TCPSocket);
      }
    }
  }
}

/* USER CODE END 1 */
