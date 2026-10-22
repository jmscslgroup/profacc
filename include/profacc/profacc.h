//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: profacc.h
//
// Code generated for Simulink model 'profacc'.
//
// Model version                  : 1.33
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Oct 27 20:51:01 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef profacc_h_
#define profacc_h_
#include "rtwtypes.h"
#include "slros_initialize.h"
#include "profacc_types.h"
#include <stddef.h>

// Block signals (default storage)
struct B_profacc_T {
  SL_Bus_profacc_std_msgs_Float64 In1; // '<S9>/In1'
  SL_Bus_profacc_std_msgs_Float64 In1_j;// '<S8>/In1'
  SL_Bus_profacc_std_msgs_Float64 In1_m;// '<S7>/In1'
};

// Block states (default storage) for system '<Root>'
struct DW_profacc_T {
  ros_slros_internal_block_GetP_T obj; // '<Root>/Get Parameter2'
  ros_slros_internal_block_GetP_T obj_n;// '<Root>/Get Parameter1'
  ros_slros_internal_block_GetP_T obj_e;// '<Root>/Get Parameter'
  ros_slroscpp_internal_block_P_T obj_nf;// '<S2>/SinkBlock'
  ros_slroscpp_internal_block_S_T obj_j;// '<S5>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_g;// '<S4>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_nfc;// '<S3>/SourceBlock'
};

// Real-time Model Data Structure
struct tag_RTM_profacc_T {
  const char_T * volatile errorStatus;
  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_profacc_T profacc_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_profacc_T profacc_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void profacc_initialize(void);
  extern void profacc_step(void);
  extern void profacc_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_profacc_T *const profacc_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'profacc'
//  '<S1>'   : 'profacc/Blank Message'
//  '<S2>'   : 'profacc/Publish'
//  '<S3>'   : 'profacc/Subscribe'
//  '<S4>'   : 'profacc/Subscribe1'
//  '<S5>'   : 'profacc/Subscribe2'
//  '<S6>'   : 'profacc/myController'
//  '<S7>'   : 'profacc/Subscribe/Enabled Subsystem'
//  '<S8>'   : 'profacc/Subscribe1/Enabled Subsystem'
//  '<S9>'   : 'profacc/Subscribe2/Enabled Subsystem'
//  '<S10>'  : 'profacc/myController/MATLAB Function'

#endif                                 // profacc_h_

//
// File trailer for generated code.
//
// [EOF]
//
