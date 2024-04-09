/**
 * General model deployment
 * 
 * Author: Pete Warden
 * Modified by: Shawn Hymel
 * Date: March 11, 2020
 * Modified by: Kishan Baranwal
 * Date: April 9, 2024
 * 
 * Copyright 2019 The TensorFlow Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */




#include "TensorFlowLite.h"
#include "tensorflow/lite/experimental/micro/kernels/micro_ops.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/experimental/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/version.h"

#include "your_model.h"

#define DEBUG 1

#define CHECK_SIZE_TO_ACCOMODATE_MODEL_CALCULATION 5
//CHANGE THIS IF ERROR OCCURED

namespace {
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* model_input = nullptr;
  TfLiteTensor* model_output = nullptr;

  constexpr int kTensorArenaSize = CHECK_SIZE_TO_ACCOMODATE_MODEL_CALCULATION * 1024;
  uint8_t tensor_arena[kTensorArenaSize];
}

void setup() {
//SERIAL is already initialized in liabrary no need for Serial.begin
#if DEBUG
  while(!Serial);
#endif

//FOR Reporting error
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(your_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report("Model version does not match Schema");
    while(1);
  }

  static tflite::MicroMutableOpResolver micro_mutable_op_resolver;
//ADD YOUR micro_ops function according to layers 
//From website https://github.com/tensorflow/tflite-micro/blob/main/tensorflow/lite/micro/kernels/micro_ops.h


//For example adding Conv2D , MaxPooling Layer
//------------------------------******************************************************
  // Add Conv2D layer
  micro_mutable_op_resolver.AddBuiltin(
    tflite::BuiltinOperator_CONV_2D,
    tflite::ops::micro::Register_CONV_2D(),
    1, 3);
  // Add MaxPooling layer
  micro_mutable_op_resolver.AddBuiltin(
    tflite::BuiltinOperator_MAX_POOL_2D,
    tflite::ops::micro::Register_MAX_POOL_2D(),
    1, 3);
//------------------------------******************************************************
 

  static tflite::MicroInterpreter static_interpreter(
    model, micro_mutable_op_resolver, tensor_arena, kTensorArenaSize,
    error_reporter);
  interpreter = &static_interpreter;

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() failed");
    while(1);
  }

  model_input = interpreter->input(0);
  model_output = interpreter->output(0);


    #if DEBUG
  Serial.print("Dimensions of input in your model");
  Serial.println(model_input->dims->size);
  #endif

  
}

void loop() {
//IF Number of input Dimensions are printed as your model inpult dimensions
/* Use similiar expressions to access input output of module
  float x_val;
  model_input->data.f[0] = x_val;
  float y_val = model_output->data.f[0];
*/
}
