#ifndef SOC_CFG_H
#define SOC_CFG_H

#include "Platform_Types.h"

/* =========================================================
 *  Common Scale / Unit Definition
 * ========================================================= */
#define BMS_SOC_SCALE_X10                  (10u)   /* SOC: 0~1000 (0.1%) */

#define BMS_UNIT_VOLTAGE_MV                (1u)
#define BMS_UNIT_CURRENT_MA                (1u)
#define BMS_UNIT_TEMP_DC                   (1u)    /* 0.1 degC */

/* =========================================================
 *  Battery Nominal Parameters
 * ========================================================= */
/* 기준: 중형 EV 팩 (≈ 50Ah 셀 * 병렬 구성 가정)
 * 구조 검증용 기본값
 */
#define BMS_SOC_NOM_CAPACITY_AH_X10        (500u)  /* 50.0 Ah */

/* Energy 계산 안 쓰면 무시 가능 */
#define BMS_SOC_NOM_ENERGY_WH_X10          (180000u) /* 18,000.0 Wh */

/* Coulomb counting efficiency (0.1% scale) */
#define BMS_SOC_EFF_CHG_X1000              (995u)   /* 99.5% */
#define BMS_SOC_EFF_DISCHG_X1000           (990u)   /* 99.0% */

/* =========================================================
 *  Coulomb Counting (CC) Config
 * ========================================================= */
#define BMS_SOC_CC_DT_MS                   (1000u) /* SoX_1000ms */

/* Current sensor characteristics */
#define BMS_SOC_CC_I_OFFSET_MA             (0)
#define BMS_SOC_CC_I_DEADBAND_MA           (300)    /* ±300mA noise cut */

/* SOC slew rate limit
 * 2.0 % / s → 20 (0.1% scale)
 */
#define BMS_SOC_CC_SLEW_LIMIT_X10_PER_S    (20u)

/* =========================================================
 *  OCV Table / Correction Config
 * ========================================================= */
/* 표준 11-point OCV table */
#define BMS_SOC_OCV_POINTS                 (11u)

/* SOC breakpoints (0.1% scale) */
extern const uint16 BmsSoc_OcvSocBp_X10[BMS_SOC_OCV_POINTS];

/* OCV table values (mV) */
extern const uint32 BmsSoc_OcvTable_mV[BMS_SOC_OCV_POINTS];

/* Rest condition detection */
#define BMS_SOC_REST_I_THR_MA              (500)     /* |I| < 0.5A */
#define BMS_SOC_REST_V_DV_THR_MV           (5)       /* dV < 5mV */
#define BMS_SOC_REST_TIME_MS               (300000u) /* 300s (5min) */

/* OCV correction behavior */
#define BMS_SOC_OCV_CORR_GAIN_X1000        (200u)   /* 20% blending */
#define BMS_SOC_OCV_CORR_MAX_STEP_X10      (30u)    /* max 3.0% per update */

/* =========================================================
 *  Clamp / Validity / Default
 * ========================================================= */
#define BMS_SOC_MIN_X10                    (0u)
#define BMS_SOC_MAX_X10                    (1000u)

/* Sensor invalid handling */
#define BMS_SOC_INVALID_HOLD_MS            (10000u) /* 10s hold */
#define BMS_SOC_INVALID_DEFAULT_X10        (500u)   /* 50% */

/* =========================================================
 *  Optional: SOC Flags
 * ========================================================= */
#define BMS_SOC_FLAG_VALID                 (0x01u)
#define BMS_SOC_FLAG_OCV_USED              (0x02u)
#define BMS_SOC_FLAG_CC_USED               (0x04u)
#define BMS_SOC_FLAG_SATURATED             (0x08u)

/* =========================================================
 *  Input sanity range (Estimator pre-check)
 *  목적:
 *   - 센서 미연결/오동작/쓰레기 값 입력 시 SoC 계산 보호
 *   - 실제 프로젝트에서는 Pack 구성/센서 스펙에 맞춰 조정
 * ========================================================= */

/* Pack Voltage sanity (mV) */
#define BMS_SOC_V_MIN_MV_SANITY            (100u)       /* 0mV/1mV 같은 비정상 값 방지 */
#define BMS_SOC_V_MAX_MV_SANITY            (200000u)    /* 샘플용 넓은 상한 (예: 200V) */

/* Pack Current sanity (mA) */
#define BMS_SOC_I_MIN_MA_SANITY            ((sint16)-500000) /* -500A */
#define BMS_SOC_I_MAX_MA_SANITY            ((sint16) 500000) /* +500A */

/* Pack Temperature sanity (0.1°C) */
#define BMS_SOC_T_MIN_DC_SANITY            ((sint16)-500)    /* -50.0°C */
#define BMS_SOC_T_MAX_DC_SANITY            ((sint16) 1250)   /* 125.0°C */


#endif /* SOC_CFG_H */
