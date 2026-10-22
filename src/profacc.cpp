//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: profacc.cpp
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
#include "profacc.h"
#include "rtwtypes.h"
#include "profacc_types.h"

// Block signals (default storage)
B_profacc_T profacc_B;

// Block states (default storage)
DW_profacc_T profacc_DW;

// Real-time model
RT_MODEL_profacc_T profacc_M_ = RT_MODEL_profacc_T();
RT_MODEL_profacc_T *const profacc_M = &profacc_M_;

// Model step function
void profacc_step(void)
{
  SL_Bus_profacc_std_msgs_Float64 rtb_BusAssignment;
  SL_Bus_profacc_std_msgs_Float64 rtb_SourceBlock_o2_f_0;
  real_T b_value;
  real_T b_value_0;
  real_T b_value_1;
  boolean_T b_varargout_1;

  // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
  // MATLABSystem: '<S4>/SourceBlock'
  b_varargout_1 = Sub_profacc_2.getLatestMessage(&rtb_SourceBlock_o2_f_0);

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  // Start for MATLABSystem: '<S4>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    profacc_B.In1_j = rtb_SourceBlock_o2_f_0;
  }

  // End of Start for MATLABSystem: '<S4>/SourceBlock'
  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe1'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe'
  // MATLABSystem: '<S3>/SourceBlock'
  b_varargout_1 = Sub_profacc_1.getLatestMessage(&rtb_SourceBlock_o2_f_0);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S7>/Enable'

  // Start for MATLABSystem: '<S3>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S7>/In1'
    profacc_B.In1_m = rtb_SourceBlock_o2_f_0;
  }

  // End of Start for MATLABSystem: '<S3>/SourceBlock'
  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe2'
  // MATLABSystem: '<S5>/SourceBlock'
  b_varargout_1 = Sub_profacc_48.getLatestMessage(&rtb_SourceBlock_o2_f_0);

  // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S9>/Enable'

  // Start for MATLABSystem: '<S5>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S9>/In1'
    profacc_B.In1 = rtb_SourceBlock_o2_f_0;
  }

  // End of Start for MATLABSystem: '<S5>/SourceBlock'
  // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe2'

  // MATLABSystem: '<Root>/Get Parameter1'
  ParamGet_profacc_19.get_parameter(&b_value);

  // MATLABSystem: '<Root>/Get Parameter'
  ParamGet_profacc_18.get_parameter(&b_value_0);

  // MATLABSystem: '<Root>/Get Parameter2'
  ParamGet_profacc_52.get_parameter(&b_value_1);

  // MATLAB Function: '<S6>/MATLAB Function' incorporates:
  //   MATLABSystem: '<Root>/Get Parameter'
  //   MATLABSystem: '<Root>/Get Parameter1'
  //   MATLABSystem: '<Root>/Get Parameter2'
  //
  b_value *= (profacc_B.In1_j.Data - b_value_0 * profacc_B.In1_m.Data) +
    b_value_1 * profacc_B.In1.Data;

  // Saturate: '<Root>/Saturation'
  if (b_value > 1.5) {
    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = 1.5;
  } else if (b_value < -3.0) {
    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = -3.0;
  } else {
    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = b_value;
  }

  // End of Saturate: '<Root>/Saturation'

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // MATLABSystem: '<S2>/SinkBlock'
  Pub_profacc_9.publish(&rtb_BusAssignment);

  // End of Outputs for SubSystem: '<Root>/Publish'
}

// Model initialize function
void profacc_initialize(void)
{
  {
    int32_T i;
    char_T b_zeroDelimTopic_0[16];
    char_T b_zeroDelimTopic[10];
    char_T b_zeroDelimTopic_1[8];
    char_T b_zeroDelimName_1[7];
    char_T b_zeroDelimName[6];
    char_T b_zeroDelimName_0[4];
    static const char_T b_zeroDelimTopic_2[10] = "cmd_accel";
    static const char_T b_zeroDelimTopic_3[10] = "lead_dist";
    static const char_T b_zeroDelimTopic_4[16] = "car/state/vel_x";
    static const char_T b_zeroDelimTopic_5[8] = "rel_vel";
    static const char_T b_zeroDelimName_2[6] = "alpha";
    static const char_T b_zeroDelimName_3[7] = "lambda";

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S2>/SinkBlock'
    profacc_DW.obj_nf.matlabCodegenIsDeleted = false;
    profacc_DW.obj_nf.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_2[i];
    }

    Pub_profacc_9.createPublisher(&b_zeroDelimTopic[0], 1);
    profacc_DW.obj_nf.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S2>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // Start for MATLABSystem: '<S4>/SourceBlock'
    profacc_DW.obj_g.matlabCodegenIsDeleted = false;
    profacc_DW.obj_g.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_3[i];
    }

    Sub_profacc_2.createSubscriber(&b_zeroDelimTopic[0], 1);
    profacc_DW.obj_g.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S3>/SourceBlock'
    profacc_DW.obj_nfc.matlabCodegenIsDeleted = false;
    profacc_DW.obj_nfc.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_4[i];
    }

    Sub_profacc_1.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    profacc_DW.obj_nfc.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S3>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe2'
    // Start for MATLABSystem: '<S5>/SourceBlock'
    profacc_DW.obj_j.matlabCodegenIsDeleted = false;
    profacc_DW.obj_j.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      b_zeroDelimTopic_1[i] = b_zeroDelimTopic_5[i];
    }

    Sub_profacc_48.createSubscriber(&b_zeroDelimTopic_1[0], 1);
    profacc_DW.obj_j.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe2'

    // Start for MATLABSystem: '<Root>/Get Parameter1'
    profacc_DW.obj_n.matlabCodegenIsDeleted = false;
    profacc_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      b_zeroDelimName[i] = b_zeroDelimName_2[i];
    }

    ParamGet_profacc_19.initialize(&b_zeroDelimName[0]);
    ParamGet_profacc_19.initialize_error_codes(0, 1, 2, 3);
    ParamGet_profacc_19.set_initial_value(1.1);
    profacc_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<Root>/Get Parameter1'

    // Start for MATLABSystem: '<Root>/Get Parameter'
    profacc_DW.obj_e.matlabCodegenIsDeleted = false;
    profacc_DW.obj_e.isInitialized = 1;
    b_zeroDelimName_0[0] = 't';
    b_zeroDelimName_0[1] = 'a';
    b_zeroDelimName_0[2] = 'u';
    b_zeroDelimName_0[3] = '\x00';
    ParamGet_profacc_18.initialize(&b_zeroDelimName_0[0]);
    ParamGet_profacc_18.initialize_error_codes(0, 1, 2, 3);
    ParamGet_profacc_18.set_initial_value(2.0);
    profacc_DW.obj_e.isSetupComplete = true;

    // Start for MATLABSystem: '<Root>/Get Parameter2'
    profacc_DW.obj.matlabCodegenIsDeleted = false;
    profacc_DW.obj.isInitialized = 1;
    for (i = 0; i < 7; i++) {
      b_zeroDelimName_1[i] = b_zeroDelimName_3[i];
    }

    ParamGet_profacc_52.initialize(&b_zeroDelimName_1[0]);
    ParamGet_profacc_52.initialize_error_codes(0, 1, 2, 3);
    ParamGet_profacc_52.set_initial_value(0.1);
    profacc_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<Root>/Get Parameter2'
  }
}

// Model terminate function
void profacc_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!profacc_DW.obj_g.matlabCodegenIsDeleted) {
    profacc_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!profacc_DW.obj_nfc.matlabCodegenIsDeleted) {
    profacc_DW.obj_nfc.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe2'
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!profacc_DW.obj_j.matlabCodegenIsDeleted) {
    profacc_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe2'

  // Terminate for MATLABSystem: '<Root>/Get Parameter1'
  if (!profacc_DW.obj_n.matlabCodegenIsDeleted) {
    profacc_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/Get Parameter1'

  // Terminate for MATLABSystem: '<Root>/Get Parameter'
  if (!profacc_DW.obj_e.matlabCodegenIsDeleted) {
    profacc_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/Get Parameter'

  // Terminate for MATLABSystem: '<Root>/Get Parameter2'
  if (!profacc_DW.obj.matlabCodegenIsDeleted) {
    profacc_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/Get Parameter2'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Terminate for MATLABSystem: '<S2>/SinkBlock'
  if (!profacc_DW.obj_nf.matlabCodegenIsDeleted) {
    profacc_DW.obj_nf.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S2>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'
}

const char_T* RT_MODEL_profacc_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_profacc_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
