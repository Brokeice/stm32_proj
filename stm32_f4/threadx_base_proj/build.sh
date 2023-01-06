# /bin/bash
SHELL_DIR=$(cd "$(dirname $0)"; pwd)
echo "${SHELL_DIR}"
MY_BUILD_TARGET_PLATFORM="arm"
MY_TARGET_OPERATION="rebuild"
MY_BUILD_TYPE="release"
MY_VERBOSE_MAKEFILE="off"
MY_PREFIX=" "
PROJECT_NAME="threax_base_proj"
IAP_FLAG="iap"

# INTERFACE_CFG=/usr/local/share/openocd/scripts/interface/cmsis-dap.cfg
# TARGET_CFG=/usr/local/share/openocd/scripts/target/stm32f4x.cfg

function usage()
{
    echo "************************Usage************************"
    echo "* ./build.sh (BUILD_TARGET_PLATFORM) [TARGET_OPERATION] [BUILD_TYPE] [VERBOSE_MAKEFILE]"
    echo "* "
    echo -e "* BUILD_TARGET_PLATFORM : \033[32m x86 / aarch64(arm) \033[0m, default: \033[31marm \033[0m"
    echo -e "* TARGET_OPERATION : \033[32m      build / clean / rebuild \033[0m, default: \033[31mrebuild \033[0m"
    echo -e "* BUILD_TYPE : \033[32m            release / debug \033[0m, default: \033[31mdebug \033[0m"
    echo -e "* VERBOSE_MAKEFILE : \033[32m      on / off \033[0m, default: \033[31moff \033[0m"
    echo "* "
    echo "* Example: ./build.sh x86 rebuild debug on"
    echo "*****************************************************"
    exit 1
}

function parse_input_parameter()
{
    for arg in $@
    do
        case ${arg,,} in
            "x86" | "aarch64" | "arm")
                MY_BUILD_TARGET_PLATFORM=${arg,,}
                if [ ${MY_BUILD_TARGET_PLATFORM} == "arm" ]
                then
                    MY_BUILD_TARGET_PLATFORM="aarch64"
                fi
                if [ ${MY_BUILD_TARGET_PLATFORM} == "aarch64" ]
                then
                    MY_PREFIX="aarch64-linux-gnu-"
                fi
                ;;
            "build" | "clean" | "rebuild")
                MY_TARGET_OPERATION=${arg,,}
                ;;
            "release" | "debug" )
                if [ ${arg,,} == "debug" ]
                then
                    MY_BUILD_TYPE="Debug"
                fi
                if [ ${arg,,} == "release" ]
                then
                    MY_BUILD_TYPE="Release"
                fi
                ;;
            "iap" | "noiap")
                IAP_FLAG=${arg,,}
                ;;
             "on" | "off")
                MY_VERBOSE_MAKEFILE=${arg,,}
                ;;
            *)
                echo -e "\033[31mInvalid parameter : ${arg}\033[0m"
                usage
                ;;
         esac
     done
     
     echo -e "\033[32m./build.sh ${MY_BUILD_TARGET_PLATFORM} ${MY_TARGET_OPERATION} ${MY_BUILD_TYPE} ${IAP_FLAG} ${MY_VERBOSE_MAKEFILE}\033[0m"
     echo -e "\033[32mUsing ${LOGIC_CPU} threads to compile ...\033[0m"
     echo " "
}

function build()
{
    mkdir -p ${SHELL_DIR}/project/release

    cd  ${SHELL_DIR}/project/release

    cmake ../.. "-G" "Unix Makefiles" "-DMY_PROJECT_NAME:string="${PROJECT_NAME} " " \
    "-DCMAKE_IAP_TYPE:string="${IAP_FLAG}" " \
    "-DBUILD_TARGET_PLATFORM:string="${MY_BUILD_TARGET_PLATFORM}" " \
    "-DCMAKE_VERBOSE_MAKEFILE:string="${MY_VERBOSE_MAKEFILE}" " \
    "-DCMAKE_BUILD_TYPE:string="${MY_BUILD_TYPE}
    make -j6

    cd ${SHELL_DIR}
    
    cp -f ${SHELL_DIR}/project/release/*.bin ${SHELL_DIR}/output/
    ls -lh ${SHELL_DIR}/project/release/
    #rm -f ${SHELL_DIR}/output/*.a 
    
    echo " "
    tree ${SHELL_DIR}/output
    echo " "
}

function clean()
{
    rm -rf ${SHELL_DIR}/project/release
    # rm -f ${SHELL_DIR}/output/*
}

function rebuild()
{
    clean
    build
}

# shell start ...
if [ $# -eq 0 ]
then
    usage
else
    parse_input_parameter $@
fi

if [ ${MY_TARGET_OPERATION} == "build" ]
then
    build
    # processing_after_compilation
elif [ ${MY_TARGET_OPERATION} == "clean" ]
then
    clean
elif [ ${MY_TARGET_OPERATION} == "rebuild" ]
then
    rebuild
    # processing_after_compilation
    # openocd -f ${INTERFACE_CFG} -f ${TARGET_CFG} -c init -c halt -c "flash write_image erase ${SHELL_DIR}/output/${PROJECT_NAME}.bin" -c reset -c shutdown
fi