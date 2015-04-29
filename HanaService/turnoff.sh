# !/bin/bash
sendevent /dev/input/event3 1 116 0
sendevent /dev/input/event3 1 116 1
sendevent /dev/input/event3 0 0 0
sleep 2
sendevent /dev/input/event3 1 116 0
sendevent /dev/input/event3 0 0 0
