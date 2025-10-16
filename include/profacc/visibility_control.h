#ifndef PROFACC__VISIBILITY_CONTROL_H_
#define PROFACC__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define PROFACC_EXPORT __attribute__ ((dllexport))
    #define PROFACC_IMPORT __attribute__ ((dllimport))
  #else
    #define PROFACC_EXPORT __declspec(dllexport)
    #define PROFACC_IMPORT __declspec(dllimport)
  #endif
  #ifdef PROFACC_BUILDING_LIBRARY
    #define PROFACC_PUBLIC PROFACC_EXPORT
  #else
    #define PROFACC_PUBLIC PROFACC_IMPORT
  #endif
  #define PROFACC_PUBLIC_TYPE PROFACC_PUBLIC
  #define PROFACC_LOCAL
#else
  #define PROFACC_EXPORT __attribute__ ((visibility("default")))
  #define PROFACC_IMPORT
  #if __GNUC__ >= 4
    #define PROFACC_PUBLIC __attribute__ ((visibility("default")))
    #define PROFACC_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define PROFACC_PUBLIC
    #define PROFACC_LOCAL
  #endif
  #define PROFACC_PUBLIC_TYPE
#endif
#endif  // PROFACC__VISIBILITY_CONTROL_H_
// Generated 15-Oct-2025 21:52:29
// Copyright 2019-2020 The MathWorks, Inc.
