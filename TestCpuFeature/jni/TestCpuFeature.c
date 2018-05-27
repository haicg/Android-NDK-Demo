/**********************************************************************
** \file TestCpuFeature.c
** \brief
** \author lihaicg
** \date Sun 27 May 2018 09:58:24 AM CST
** Mail:  lihaicg@126.com
************************************************************************/

#include <stdio.h>
#include <cpu-features.h>



#define MAX_FEATURE_NUM 17



typedef struct CpuFeatureInfo_s {
    uint64_t featureKey;
    const char *featureMsg;
} CpuFeatureInfo;



const char msgVFPv2[] = "VFPv2:\n" \
  "CPU supports the VFPv2 instruction set. Many, but not all, ARMv6 CPUs " \
  "support these instructions. VFPv2 is a subset of VFPv3 so this will "\
  "be set whenever VFPv3 is set too.";

const char msgARMv7[] = "ARMv7:\n" \
  "CPU supports the ARMv7-A basic instruction set. This feature is mandated by the 'armeabi-v7a' ABI.";

const char msgVFPv3[] = "VFPv3: \n" \
  "CPU supports the VFPv3-D16 instruction set, providing hardware FPU support for single and double precision floating point registers. Note that only 16 FPU registers are available by default, unless the D32 bit is set too. This feature is also mandated by the 'armeabi-v7a' ABI.";

const char msgVFP_D32[] = "VFP_D32:\n"\
  "CPU VFP optional extension that provides 32 FPU registers, instead of 16. Note that ARM mandates this feature is the 'NEON' feature is implemented by the CPU.";

const char msgNEON[] = "NEON: \n"\
  "CPU FPU supports \"ARM Advanced SIMD\" instructions, also known as NEON. Note that this mandates the VFP_D32 feature as well, per the ARM Architecture specification.";

const char msgVFP_FP16[] = "VFP_FP16:\n"\
  "Half-width floating precision VFP extension. If set, the CPU supports instructions to perform floating-point operations on 16-bit registers. This is part of the VFPv4 specification, but not mandated by any Android ABI.";

const char msgVFP_FMA[] = "VFP_FMA:\n "\
  "Fused multiply-accumulate VFP instructions extension. Also part of the VFPv4 specification, but not mandated by any Android ABI.";

const char msgNEON_FMA[] = "NEON_FMA:\n" \
  "Fused multiply-accumulate NEON instructions extension. Optional extension from the VFPv4 specification, but not mandated by any Android ABI.";

const char msgIDIV_ARM[] = "IDIV_ARM:\n" \
  "Integer division available in ARM mode. Only available on recent CPUs (e.g. Cortex-A15).";

const char msgIDIV_THUMB2[] = "IDIV_THUMB2:\n" \
  "Integer division available in Thumb-2 mode. Only available "\
  "on recent CPUs (e.g. Cortex-A15).";

const char msgiWMMXt[] = "iWMMXt:\n"\
  "Optional extension that adds MMX registers and operations to an "\
  "ARM CPU. This is only available on a few XScale-based CPU designs "\
  "sold by Marvell. Pretty rare in practice.";

const char msgAES[] = "AES:\n" \
  "CPU supports AES instructions. These instructions are only "\
  "available for 32-bit applications running on ARMv8 CPU.";

const char msgCRC32[] = "CRC32:\n" \
  "CPU supports CRC32 instructions. These instructions are only "\
  "available for 32-bit applications running on ARMv8 CPU.";

const char msgSHA2[] = "SHA2:\n" \
  "CPU supports SHA2 instructions. These instructions are only "\
  "available for 32-bit applications running on ARMv8 CPU.";

const char msgSHA1[] = "SHA1:\n" \
  "CPU supports SHA1 instructions. These instructions are only " \
  "available for 32-bit applications running on ARMv8 CPU.";

const char msgPMULL[] = "PMULL:\n "\
  "CPU supports 64-bit PMULL and PMULL2 instructions. These instructions are only available for 32-bit applications running on ARMv8 CPU.";

const char msgLDREX_STREX[] = "LDREX_STREX:\n" \
   "Use LDREX and STREX to implement interprocess communication " \
   "in multiple-processor and shared-memory systems. "\
   "For reasons of performance, keep the number of instructions " \
   "between corresponding LDREX and STREX instruction to a minimum";

CpuFeatureInfo allFeatures[] = {
    { ANDROID_CPU_ARM_FEATURE_ARMv7         , msgARMv7          },
    { ANDROID_CPU_ARM_FEATURE_VFPv3         , msgVFPv3          },
    { ANDROID_CPU_ARM_FEATURE_NEON          , msgNEON           },
    { ANDROID_CPU_ARM_FEATURE_LDREX_STREX   , msgLDREX_STREX    },
    { ANDROID_CPU_ARM_FEATURE_VFPv2         , msgVFPv2          },
    { ANDROID_CPU_ARM_FEATURE_VFP_D32       , msgVFP_D32        },
    { ANDROID_CPU_ARM_FEATURE_VFP_FP16      , msgVFP_FP16       },
    { ANDROID_CPU_ARM_FEATURE_VFP_FMA       , msgVFP_FMA        },
    { ANDROID_CPU_ARM_FEATURE_NEON_FMA      , msgNEON_FMA       },
    { ANDROID_CPU_ARM_FEATURE_IDIV_ARM      , msgIDIV_ARM       },
    { ANDROID_CPU_ARM_FEATURE_IDIV_THUMB2   , msgIDIV_THUMB2    },
    { ANDROID_CPU_ARM_FEATURE_iWMMXt        , msgiWMMXt         },
    { ANDROID_CPU_ARM_FEATURE_AES           , msgAES            },
    { ANDROID_CPU_ARM_FEATURE_PMULL         , msgPMULL          },
    { ANDROID_CPU_ARM_FEATURE_SHA1          , msgSHA1           },
    { ANDROID_CPU_ARM_FEATURE_SHA2          , msgSHA2           },
    { ANDROID_CPU_ARM_FEATURE_CRC32         , msgCRC32          }
};


static AndroidCpuFamily m_cpuFamily;
static uint64_t m_cpuFeatures;
static int m_cpuCount;



void printCpuFamily(AndroidCpuFamily f)
{
    const char *msg = "UNKNOWN";
    switch (f) {
        case ANDROID_CPU_FAMILY_ARM:
            msg = "ARM";
            break;
        case ANDROID_CPU_FAMILY_ARM64:
            msg = "ARM64";
            break;
        case ANDROID_CPU_FAMILY_MIPS:
            msg = "MIPS";
            break;
        case ANDROID_CPU_FAMILY_MIPS64:
            msg = "MIPS64";
            break;
        case ANDROID_CPU_FAMILY_X86:
            msg = "X86";
            break;
        case ANDROID_CPU_FAMILY_X86_64:
            msg = "X86_64";
            break;
        default:
            msg = "UNKNOWN";
    }
    printf("Cpu Family %s \n", msg);
    return;
}

const char *getOneCpuFeatures(int index, uint64_t k)
{
    const int max = sizeof(allFeatures)/sizeof(allFeatures[0]);
    if (index <= max && allFeatures[index].featureKey == k) {
        return allFeatures[index].featureMsg;
    }
    return NULL;
}

void printfCpuFeatures(uint64_t feature)
{
    int i = 0;
    uint64_t mask = 0;
    printf("Cpu Features List : (Comment Copy from cpu-features.h)\n");
    for (i = 0; i < MAX_FEATURE_NUM; i++) {
        mask = 0x01 << i;
        if (feature & mask) {
            const char *msg = getOneCpuFeatures(i, mask);
            if (msg != NULL) {
                printf("%s\n\n", msg);
            }
        }
    }
}

void printfCpuCount(int n)
{
    printf("%d processor\n", n);
}

int main(int argc,char *argv[])
{
    printf("Welcome To Cpu Word\n");
    m_cpuFamily = android_getCpuFamily();
    m_cpuCount = android_getCpuCount();
    printCpuFamily(m_cpuFamily);
    printfCpuCount(m_cpuCount);
    m_cpuFeatures = android_getCpuFeatures();
    printfCpuFeatures(m_cpuFeatures);
    return 0;
}

