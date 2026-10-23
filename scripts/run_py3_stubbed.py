#!/usr/bin/env python3
"""Run a ROS python node whose unused imports are not installed.

gps2vsl's leadVelProcessing.py imports pandas and requests but never uses
them, and the rossim Docker image has neither. This puts empty stand-in
modules in their place, then runs the node unchanged. Docker replays only;
the car has the real packages.

Use it as a launch-prefix:
    launch-prefix="python3 $(find profacc)/scripts/run_py3_stubbed.py"
"""
import runpy
import sys
import types

for name in ('pandas', 'requests'):
    try:
        __import__(name)
    except ImportError:
        sys.modules[name] = types.ModuleType(name)

# roslaunch appends the node's path and its arguments after the prefix
script = sys.argv[1]
sys.argv = sys.argv[1:]
runpy.run_path(script, run_name='__main__')
