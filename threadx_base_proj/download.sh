SHELL_DIR=$(cd "$(dirname $0)"; pwd)
echo "${SHELL_DIR}"

PROJECT_NAME="threax_base_proj"


INTERFACE_CFG=/usr/local/share/openocd/scripts/interface/cmsis-dap.cfg
TARGET_CFG=/usr/local/share/openocd/scripts/target/stm32f4x.cfg


    openocd -f ${INTERFACE_CFG} -f ${TARGET_CFG} -c init -c halt -c "flash write_image erase ${SHELL_DIR}/output/${PROJECT_NAME}.bin" -c reset -c shutdown
