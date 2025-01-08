#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-SHT21.mk)" "nbproject/Makefile-local-SHT21.mk"
include nbproject/Makefile-local-SHT21.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=SHT21
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SHT21.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SHT21.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Libraries/LCD/GLCDnokia.c ../Libraries/LCD/charSet16x7.c ../Libraries/LCD/charSet8x5.c ../Libraries/PLIB/plib18fxxk22.c ../Libraries/SHT21/SHT21.c main_sht21.c uC_config.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1 ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1 ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1 ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1 ${OBJECTDIR}/_ext/1585182137/SHT21.p1 ${OBJECTDIR}/main_sht21.p1 ${OBJECTDIR}/uC_config.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1.d ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1.d ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1.d ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1.d ${OBJECTDIR}/_ext/1585182137/SHT21.p1.d ${OBJECTDIR}/main_sht21.p1.d ${OBJECTDIR}/uC_config.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1 ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1 ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1 ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1 ${OBJECTDIR}/_ext/1585182137/SHT21.p1 ${OBJECTDIR}/main_sht21.p1 ${OBJECTDIR}/uC_config.p1

# Source Files
SOURCEFILES=../Libraries/LCD/GLCDnokia.c ../Libraries/LCD/charSet16x7.c ../Libraries/LCD/charSet8x5.c ../Libraries/PLIB/plib18fxxk22.c ../Libraries/SHT21/SHT21.c main_sht21.c uC_config.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-SHT21.mk ${DISTDIR}/SHT21.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F25K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1: ../Libraries/LCD/GLCDnokia.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1178244344" 
	@${RM} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1 ../Libraries/LCD/GLCDnokia.c 
	@-${MV} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.d ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1178244344/charSet16x7.p1: ../Libraries/LCD/charSet16x7.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1178244344" 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1 ../Libraries/LCD/charSet16x7.c 
	@-${MV} ${OBJECTDIR}/_ext/1178244344/charSet16x7.d ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1178244344/charSet8x5.p1: ../Libraries/LCD/charSet8x5.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1178244344" 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1 ../Libraries/LCD/charSet8x5.c 
	@-${MV} ${OBJECTDIR}/_ext/1178244344/charSet8x5.d ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1: ../Libraries/PLIB/plib18fxxk22.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2129259034" 
	@${RM} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1 ../Libraries/PLIB/plib18fxxk22.c 
	@-${MV} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.d ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1585182137/SHT21.p1: ../Libraries/SHT21/SHT21.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1585182137" 
	@${RM} ${OBJECTDIR}/_ext/1585182137/SHT21.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1585182137/SHT21.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1585182137/SHT21.p1 ../Libraries/SHT21/SHT21.c 
	@-${MV} ${OBJECTDIR}/_ext/1585182137/SHT21.d ${OBJECTDIR}/_ext/1585182137/SHT21.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1585182137/SHT21.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main_sht21.p1: main_sht21.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_sht21.p1.d 
	@${RM} ${OBJECTDIR}/main_sht21.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main_sht21.p1 main_sht21.c 
	@-${MV} ${OBJECTDIR}/main_sht21.d ${OBJECTDIR}/main_sht21.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main_sht21.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/uC_config.p1: uC_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uC_config.p1.d 
	@${RM} ${OBJECTDIR}/uC_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/uC_config.p1 uC_config.c 
	@-${MV} ${OBJECTDIR}/uC_config.d ${OBJECTDIR}/uC_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/uC_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1: ../Libraries/LCD/GLCDnokia.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1178244344" 
	@${RM} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1 ../Libraries/LCD/GLCDnokia.c 
	@-${MV} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.d ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1178244344/GLCDnokia.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1178244344/charSet16x7.p1: ../Libraries/LCD/charSet16x7.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1178244344" 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1 ../Libraries/LCD/charSet16x7.c 
	@-${MV} ${OBJECTDIR}/_ext/1178244344/charSet16x7.d ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1178244344/charSet16x7.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1178244344/charSet8x5.p1: ../Libraries/LCD/charSet8x5.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1178244344" 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1 ../Libraries/LCD/charSet8x5.c 
	@-${MV} ${OBJECTDIR}/_ext/1178244344/charSet8x5.d ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1178244344/charSet8x5.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1: ../Libraries/PLIB/plib18fxxk22.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2129259034" 
	@${RM} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1 ../Libraries/PLIB/plib18fxxk22.c 
	@-${MV} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.d ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2129259034/plib18fxxk22.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1585182137/SHT21.p1: ../Libraries/SHT21/SHT21.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1585182137" 
	@${RM} ${OBJECTDIR}/_ext/1585182137/SHT21.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1585182137/SHT21.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/1585182137/SHT21.p1 ../Libraries/SHT21/SHT21.c 
	@-${MV} ${OBJECTDIR}/_ext/1585182137/SHT21.d ${OBJECTDIR}/_ext/1585182137/SHT21.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1585182137/SHT21.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main_sht21.p1: main_sht21.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_sht21.p1.d 
	@${RM} ${OBJECTDIR}/main_sht21.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main_sht21.p1 main_sht21.c 
	@-${MV} ${OBJECTDIR}/main_sht21.d ${OBJECTDIR}/main_sht21.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main_sht21.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/uC_config.p1: uC_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uC_config.p1.d 
	@${RM} ${OBJECTDIR}/uC_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -DXPRJ_SHT21=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/uC_config.p1 uC_config.c 
	@-${MV} ${OBJECTDIR}/uC_config.d ${OBJECTDIR}/uC_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/uC_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SHT21.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SHT21.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit3  -DXPRJ_SHT21=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SHT21.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/SHT21.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/SHT21.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SHT21.X.${IMAGE_TYPE}.map  -DXPRJ_SHT21=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"./" -I"../Libraries/" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SHT21.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
