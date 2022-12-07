
#ifndef ERRNO_EXT_H
#define ERRNO_EXT_H

#define ERRNO_SUCCESS            0
#define ERRNO_BASE               10
#define ERRNO_INVALID_PARAM      (ERRNO_BASE + 1)
#define ERRNO_PARAM              ERRNO_INVALID_PARAM
#define ERRNO_NULL_POINTER       (ERRNO_BASE + 2)
#define ERRNO_INIT               (ERRNO_BASE + 3)
#define ERRNO_TIMEOUT            (ERRNO_BASE + 4)
#define ERRNO_TRANSADDR          (ERRNO_BASE + 5)
#define ERRNO_TRANSDATA          (ERRNO_BASE + 6)
#define ERRNO_READDATA           (ERRNO_BASE + 7)
#define ERRNO_TRANSCMD           (ERRNO_BASE + 8)
#define ERRNO_BUF_LEN            (ERRNO_BASE + 9)
#define ERRNO_MALLOC             (ERRNO_BASE + 10)
#define ERRNO_NOT_SUPPORT        (ERRNO_BASE + 11)
#define ERRNO_BUSY               (ERRNO_BASE + 12)
#define ERRNO_DEV_OPEN           (ERRNO_BASE + 13)
#define ERRNO_DEV_CLOSE          (ERRNO_BASE + 14)
#define ERRNO_DEV_WR             (ERRNO_BASE + 15)
#define ERRNO_DEV_RD             (ERRNO_BASE + 16)
#define ERRNO_DEV_RST            (ERRNO_BASE + 17)
#define ERRNO_BDTYPE             (ERRNO_BASE + 18)
#define ERRNO_POWER_OFF          (ERRNO_BASE + 19)
#define ERRNO_DEV_OFFLINE        (ERRNO_BASE + 20)
#define ERRNO_BAD_CRC            (ERRNO_BASE + 21)
#define ERRNO_CRC_ERR            (ERRNO_BASE + 22)
#define ERRNO_CLK_RST_ERR        (ERRNO_BASE + 23)

#define ERRNO_FLASH_BASE         50
#define ERRNO_FLASH_SENDCMD      (ERRNO_FLASH_BASE + 1)
#define ERRNO_FLASH_RDDATA       (ERRNO_FLASH_BASE + 2)
#define ERRNO_FLASH_WRDATA       (ERRNO_FLASH_BASE + 3)
#define ERRNO_FLASH_WRADDR       (ERRNO_FLASH_BASE + 4)
#define ERRNO_FLASH_WREN         (ERRNO_FLASH_BASE + 5)
#define ERRNO_FLASH_WRDIS        (ERRNO_FLASH_BASE + 6)
#define ERRNO_FLASH_WRTIMEOUT    (ERRNO_FLASH_BASE + 7)
#define ERRNO_FLASH_ERASE        (ERRNO_FLASH_BASE + 8)
#define ERRNO_FLASH_RDREG        (ERRNO_FLASH_BASE + 9)
#define ERRNO_FLASH_WRREG        (ERRNO_FLASH_BASE + 10)
#define ERRNO_FLASH_PAGE         (ERRNO_FLASH_BASE + 11)
#define ERRNO_FLASH_OPEN         (ERRNO_FLASH_BASE + 12)
#define ERRNO_FLASH_CLOSE        (ERRNO_FLASH_BASE + 13)
#define ERRNO_FLASH_LOCK         (ERRNO_FLASH_BASE + 13)
#define ERRNO_FLASH_UNLOCK       (ERRNO_FLASH_BASE + 13)

#define ERRNO_FILE_BASE          70
#define ERRNO_FILE_NAME          (ERRNO_FILE_BASE + 1)
#define ERRNO_FILE_NONEXIST      (ERRNO_FILE_BASE + 2)
#define ERRNO_FILE_LEN           (ERRNO_FILE_BASE + 3)
#define ERRNO_FILE_OPEN          (ERRNO_FILE_BASE + 4)
#define ERRNO_FILE_CLOSE         (ERRNO_FILE_BASE + 5)
#define ERRNO_FILE_WRITE         (ERRNO_FILE_BASE + 6)
#define ERRNO_FILE_READ          (ERRNO_FILE_BASE + 7)
#define ERRNO_FILE_ERASE         (ERRNO_FILE_BASE + 8)
#define ERRNO_FILE_CHECK         (ERRNO_FILE_BASE + 9)
#define ERRNO_FILE_VER           (ERRNO_FILE_BASE + 10)
#define ERRNO_FILE_TYPE          (ERRNO_FILE_BASE + 11)
#define ERRNO_FILE_SYNC          (ERRNO_FILE_BASE + 12)
#define ERRNO_FILE_COMPRESS      (ERRNO_FILE_BASE + 13)
#define ERRNO_FILE_UNCOMPRESS    (ERRNO_FILE_BASE + 14)
#define ERRNO_FILE_SEEK          (ERRNO_FILE_BASE + 15)
#define ERRNO_FILE_TELL          (ERRNO_FILE_BASE + 16)
#define ERRNO_FILE_TURN          (ERRNO_FILE_BASE + 17)
#define ERRNO_FILE_RENAME        (ERRNO_FILE_BASE + 18)
#define ERRNO_FILE_SYSTEM_INIT   (ERRNO_FILE_BASE + 19)
#define ERRNO_FILE_SYSTEM_PARTITON   (ERRNO_FILE_BASE + 20)
#define ERRNO_FILE_SYSTEM_FORMAT     (ERRNO_FILE_BASE + 21)
#define ERRNO_FILE_SYSTEM_MOUNT      (ERRNO_FILE_BASE + 22)
#define ERRNO_FILE_SYSTEM_DIR_MK     (ERRNO_FILE_BASE + 23)
#define ERRNO_FILE_SYSTEM_DIR_RM     (ERRNO_FILE_BASE + 24)
#define ERRNO_FILE_SYSTEM_DIR_CD     (ERRNO_FILE_BASE + 25)
#define ERRNO_FILE_SYSTEM_DIR_PWD    (ERRNO_FILE_BASE + 26)
#define ERRNO_FILE_SYSTEM_DIR_FREE   (ERRNO_FILE_BASE + 27)

#define ERRNO_FPGA_BASE          100
#define ERRNO_FPGA_DONE          (ERRNO_FPGA_BASE + 1)
#define ERRNO_FPGA_TEST          (ERRNO_FPGA_BASE + 2)
#define ERRNO_FPGA_SEND          (ERRNO_FPGA_BASE + 3)
#define ERRNO_FPGA_LOAD          (ERRNO_FPGA_BASE + 4)

#define ERRNO_PHY_BASE           120
#define ERRNO_PHY_READ           (ERRNO_PHY_BASE + 1)
#define ERRNO_PHY_WRITE          (ERRNO_PHY_BASE + 2)
#define ERRNO_PHY_ADDR           (ERRNO_PHY_BASE + 3)

#define ERRNO_FPGA_IIC_BASE       160
#define ERRNO_FPGA_IIC_READ       (ERRNO_FPGA_IIC_BASE + 1)
#define ERRNO_FPGA_IIC_WRITE      (ERRNO_FPGA_IIC_BASE + 2)
#define ERRNO_FPGA_IIC_ADDR       (ERRNO_FPGA_IIC_BASE + 3)
#define ERRNO_FPGA_IIC_CMD        (ERRNO_FPGA_IIC_BASE + 4)
#define ERRNO_FPGA_IIC_OPEN       (ERRNO_FPGA_IIC_BASE + 5)
#define ERRNO_FPGA_IIC_CLOSE      (ERRNO_FPGA_IIC_BASE + 6)

#define ERRNO_RTC_BASE            240
#define ERRNO_RTC_INIT            (ERRNO_RTC_BASE + 1)
#define ERRNO_RTC_TIME            (ERRNO_RTC_BASE + 2)
#define ERRNO_RTC_DATE            (ERRNO_RTC_BASE + 3)

#define ERRNO_MB_BASE            260
#define ERRNO_MB_SEND            (ERRNO_MB_BASE + 1)
#define ERRNO_MB_RECV            (ERRNO_MB_BASE + 2)
#define ERRNO_MB_LEN             (ERRNO_MB_BASE + 3)

#define ERRNO_I2C_BASE           280
#define ERRNO_I2C_READ           (ERRNO_I2C_BASE + 1)
#define ERRNO_I2C_WRITE          (ERRNO_I2C_BASE + 2)
#define ERRNO_I2C_OPEN           (ERRNO_I2C_BASE + 2)
#define ERRNO_I2C_CLOSE          (ERRNO_I2C_BASE + 3)

#define ERRNO_SOCKET_BASE        400
#define ERRNO_SOCKET_CEATE       (ERRNO_SOCKET_BASE + 1)
#define ERRNO_SOCKET_BIND        (ERRNO_SOCKET_BASE + 2)
#define ERRNO_SOCKET_SEND        (ERRNO_SOCKET_BASE + 3)
#define ERRNO_SOCKET_RECV        (ERRNO_SOCKET_BASE + 4)

#define ERRNO_TFTP_BASE            440
#define ERRNO_TFTP_CONNECT_SERVER  (ERRNO_TFTP_BASE + 1)
#define ERRNO_TFTP_SEND_REQ        (ERRNO_TFTP_BASE + 2)
#define ERRNO_TFTP_SEND_ACK        (ERRNO_TFTP_BASE + 3)
#define ERRNO_TFTP_WAIT_ACK        (ERRNO_TFTP_BASE + 4)
#define ERRNO_TFTP_PKT_LEN         (ERRNO_TFTP_BASE + 5)
#define ERRNO_TFTP_OPCODE          (ERRNO_TFTP_BASE + 6)

#define ERRNO_RTOS_BASE          500
#define ERRNO_QUEUE_CREATE       (ERRNO_RTOS_BASE + 1)
#define ERRNO_QUEUE_SEND         (ERRNO_RTOS_BASE + 2)
#define ERRNO_TASK_CREATE        (ERRNO_RTOS_BASE + 10)
#define ERRNO_SEM_CREATE         (ERRNO_RTOS_BASE + 20)
#define ERRNO_SEM_TAKE           (ERRNO_RTOS_BASE + 21)
#define ERRNO_SEM_GIVE           (ERRNO_RTOS_BASE + 22)
#define ERRNO_TIMERS_CREATE      (ERRNO_RTOS_BASE + 30)
#define ERRNO_TIMERS_START       (ERRNO_RTOS_BASE + 31)

#define ERRNO_ETH_BASE           700
#define ERRNO_ETH_PACKET_HEAD_CHECK       (ERRNO_ETH_BASE + 1)
#define ERRNO_ETH_PACKET_CRC_CHECK        (ERRNO_ETH_BASE + 2)
#define ERRNO_ETH_MSG_HEAD_CHECK          (ERRNO_ETH_BASE + 3)

#define ERRNO_FILE_UPD_BASE        800
#define ERRNO_FILE_UPD_REQSND      (ERRNO_FILE_UPD_BASE + 1)
#define ERRNO_FILE_UPD_STARTSND    (ERRNO_FILE_UPD_BASE + 2)
#define ERRNO_FILE_UPD_RESTARTSND  (ERRNO_FILE_UPD_BASE + 3)
#define ERRNO_FILE_UPD_DATASND     (ERRNO_FILE_UPD_BASE + 4)
#define ERRNO_FILE_UPD_ENDSND      (ERRNO_FILE_UPD_BASE + 5)
#define ERRNO_FILE_UPD_ACTI        (ERRNO_FILE_UPD_BASE + 6)


#define  EPERM            1  /* Operation not permitted */
#define  ENOENT           2  /* No such file or directory */
#define  ESRCH            3  /* No such process */
#define  EINTR            4  /* Interrupted system call */
#define  EIO              5  /* I/O error */
#define  ENXIO            6  /* No such device or address */
#define  E2BIG            7  /* Arg list too long */
#define  ENOEXEC          8  /* Exec format error */
#define  EBADF            9  /* Bad file number */
#define  ECHILD          10  /* No child processes */
#define  EAGAIN          11  /* Try again */
// #define  ENOMEM          12  /* Out of memory */
#define  EACCES          13  /* Permission denied */
#define  EFAULT          14  /* Bad address */
#define  ENOTBLK         15  /* Block device required */
#define  EBUSY           16  /* Device or resource busy */
#define  EEXIST          17  /* File exists */
#define  EXDEV           18  /* Cross-device link */
#define  ENODEV          19  /* No such device */
#define  ENOTDIR         20  /* Not a directory */
#define  EISDIR          21  /* Is a directory */
#define  EINVAL          22  /* Invalid argument */
#define  ENFILE          23  /* File table overflow */
#define  EMFILE          24  /* Too many open files */
#define  ENOTTY          25  /* Not a typewriter */
#define  ETXTBSY         26  /* Text file busy */
#define  EFBIG           27  /* File too large */
#define  ENOSPC          28  /* No space left on device */
#define  ESPIPE          29  /* Illegal seek */
#define  EROFS           30  /* Read-only file system */
#define  EMLINK          31  /* Too many links */
#define  EPIPE           32  /* Broken pipe */
// #define  EDOM            33  /* Math argument out of domain of func */
// #define  ERANGE          34  /* Math result not representable */
#define  EDEADLK         35  /* Resource deadlock would occur */
#define  ENAMETOOLONG    36  /* File name too long */
#define  ENOLCK          37  /* No record locks available */
#define  ENOSYS          38  /* Function not implemented */
#define  ENOTEMPTY       39  /* Directory not empty */
#define  ELOOP           40  /* Too many symbolic links encountered */
#define  EWOULDBLOCK     EAGAIN  /* Operation would block */
#define  ENOMSG          42  /* No message of desired type */
#define  EIDRM           43  /* Identifier removed */
#define  ECHRNG          44  /* Channel number out of range */
#define  EL2NSYNC        45  /* Level 2 not synchronized */
#define  EL3HLT          46  /* Level 3 halted */
#define  EL3RST          47  /* Level 3 reset */
#define  ELNRNG          48  /* Link number out of range */
#define  EUNATCH         49  /* Protocol driver not attached */
#define  ENOCSI          50  /* No CSI structure available */
#define  EL2HLT          51  /* Level 2 halted */
#define  EBADE           52  /* Invalid exchange */
#define  EBADR           53  /* Invalid request descriptor */
#define  EXFULL          54  /* Exchange full */
#define  ENOANO          55  /* No anode */
#define  EBADRQC         56  /* Invalid request code */
#define  EBADSLT         57  /* Invalid slot */

#define  EDEADLOCK       EDEADLK

#define  EBFONT          59  /* Bad font file format */
#define  ENOSTR          60  /* Device not a stream */
#define  ENODATA         61  /* No data available */
#define  ETIME           62  /* Timer expired */
#define  ENOSR           63  /* Out of streams resources */
#define  ENONET          64  /* Machine is not on the network */
#define  ENOPKG          65  /* Package not installed */
#define  EREMOTE         66  /* Object is remote */
#define  ENOLINK         67  /* Link has been severed */
#define  EADV            68  /* Advertise error */
#define  ESRMNT          69  /* Srmount error */
#define  ECOMM           70  /* Communication error on send */
#define  EPROTO          71  /* Protocol error */
#define  EMULTIHOP       72  /* Multihop attempted */
#define  EDOTDOT         73  /* RFS specific error */
#define  EBADMSG         74  /* Not a data message */
#define  EOVERFLOW       75  /* Value too large for defined data type */
#define  ENOTUNIQ        76  /* Name not unique on network */
#define  EBADFD          77  /* File descriptor in bad state */
#define  EREMCHG         78  /* Remote address changed */
#define  ELIBACC         79  /* Can not access a needed shared library */
#define  ELIBBAD         80  /* Accessing a corrupted shared library */
#define  ELIBSCN         81  /* .lib section in a.out corrupted */
#define  ELIBMAX         82  /* Attempting to link in too many shared libraries */
#define  ELIBEXEC        83  /* Cannot exec a shared library directly */
// #define  EILSEQ          84  /* Illegal byte sequence */
#define  ERESTART        85  /* Interrupted system call should be restarted */
#define  ESTRPIPE        86  /* Streams pipe error */
#define  EUSERS          87  /* Too many users */
#define  ENOTSOCK        88  /* Socket operation on non-socket */
#define  EDESTADDRREQ    89  /* Destination address required */
#define  EMSGSIZE        90  /* Message too long */
#define  EPROTOTYPE      91  /* Protocol wrong type for socket */
#define  ENOPROTOOPT     92  /* Protocol not available */
#define  EPROTONOSUPPORT 93  /* Protocol not supported */
#define  ESOCKTNOSUPPORT 94  /* Socket type not supported */
#define  EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define  EPFNOSUPPORT    96  /* Protocol family not supported */
#define  EAFNOSUPPORT    97  /* Address family not supported by protocol */
#define  EADDRINUSE      98  /* Address already in use */
#define  EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define  ENETDOWN       100  /* Network is down */
#define  ENETUNREACH    101  /* Network is unreachable */
#define  ENETRESET      102  /* Network dropped connection because of reset */
#define  ECONNABORTED   103  /* Software caused connection abort */
#define  ECONNRESET     104  /* Connection reset by peer */
#define  ENOBUFS        105  /* No buffer space available */
#define  EISCONN        106  /* Transport endpoint is already connected */
#define  ENOTCONN       107  /* Transport endpoint is not connected */
#define  ESHUTDOWN      108  /* Cannot send after transport endpoint shutdown */
#define  ETOOMANYREFS   109  /* Too many references: cannot splice */
#define  ETIMEDOUT      110  /* Connection timed out */
#define  ECONNREFUSED   111  /* Connection refused */
#define  EHOSTDOWN      112  /* Host is down */
#define  EHOSTUNREACH   113  /* No route to host */
#define  EALREADY       114  /* Operation already in progress */
#define  EINPROGRESS    115  /* Operation now in progress */
#define  ESTALE         116  /* Stale NFS file handle */
#define  EUCLEAN        117  /* Structure needs cleaning */
#define  ENOTNAM        118  /* Not a XENIX named type file */
#define  ENAVAIL        119  /* No XENIX semaphores available */
#define  EISNAM         120  /* Is a named type file */
#define  EREMOTEIO      121  /* Remote I/O error */
#define  EDQUOT         122  /* Quota exceeded */

#define  ENOMEDIUM      123  /* No medium found */
#define  EMEDIUMTYPE    124  /* Wrong medium type */

#define  ENOTSUP        125  /* Unsupported value */

#endif
