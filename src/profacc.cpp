//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: profacc.cpp
//
// Code generated for Simulink model 'profacc'.
//
// Model version                  : 1.9
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Oct 14 10:10:23 2025
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
  SL_Bus_profacc_std_msgs_Float64 rtb_SourceBlock_o2_0;
  boolean_T b_varargout_1;

  // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
  // MATLABSystem: '<S5>/SourceBlock'
  b_varargout_1 = Sub_profacc_2.getLatestMessage(&rtb_SourceBlock_o2_0);

  // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  // Start for MATLABSystem: '<S5>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    profacc_B.In1 = rtb_SourceBlock_o2_0;
  }

  // End of Start for MATLABSystem: '<S5>/SourceBlock'
  // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe1'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe'
  // MATLABSystem: '<S4>/SourceBlock'
  b_varargout_1 = Sub_profacc_1.getLatestMessage(&rtb_SourceBlock_o2_0);

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S7>/Enable'

  // Start for MATLABSystem: '<S4>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S7>/In1'
    profacc_B.In1_m = rtb_SourceBlock_o2_0;
  }

  // End of Start for MATLABSystem: '<S4>/SourceBlock'
  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe'

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function1'

  rtb_BusAssignment.Data = (profacc_B.In1.Data - 0.1 * profacc_B.In1_m.Data) *
    0.1;

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // MATLABSystem: '<S3>/SinkBlock'
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
    static const char_T b_zeroDelimTopic_1[10] = "cmd_accel";
    static const char_T b_zeroDelimTopic_2[10] = "lead_dist";
    static const char_T b_zeroDelimTopic_3[16] = "car/state/vel_x";

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S3>/SinkBlock'
    profacc_DW.obj.matlabCodegenIsDeleted = false;
    profacc_DW.obj.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_1[i];
    }

    Pub_profacc_9.createPublisher(&b_zeroDelimTopic[0], 1);
    profacc_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S3>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // Start for MATLABSystem: '<S5>/SourceBlock'
    profacc_DW.obj_g.matlabCodegenIsDeleted = false;
    profacc_DW.obj_g.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_2[i];
    }

    Sub_profacc_2.createSubscriber(&b_zeroDelimTopic[0], 1);
    profacc_DW.obj_g.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S4>/SourceBlock'
    profacc_DW.obj_n.matlabCodegenIsDeleted = false;
    profacc_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_3[i];
    }

    Sub_profacc_1.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    profacc_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'
  }
}

// Model terminate function
void profacc_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!profacc_DW.obj_g.matlabCodegenIsDeleted) {
    profacc_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!profacc_DW.obj_n.matlabCodegenIsDeleted) {
    profacc_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Terminate for MATLABSystem: '<S3>/SinkBlock'
  if (!profacc_DW.obj.matlabCodegenIsDeleted) {
    profacc_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S3>/SinkBlock'
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
