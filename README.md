# ALogger
A custom wrapping to spdlog for multiple logger/sinks at once. Aim was to have console, file and null logging in place, and to enable/disable them at runtime. 

Running benchmark (<a href="https://github.com/gabime/spdlog/tree/v1.x/bench">bench.cpp</a>) gives similar metrics as one run on plain spdlog benchmark test<br>
<b>Stats:</b>
```

08:30:06: Starting /home/shekhar/workspace/core/piModule/logging/build-bench-Desktop_Qt5_12_4-Debug/bench ...
[2021-11-26 08:30:06.057] [consoleLogger] [info] [bench.cpp:76] **************************************************************
[2021-11-26 08:30:06.057] [consoleLogger] [info] [bench.cpp:77] Single threaded: 250000 messages
[2021-11-26 08:30:06.057] [consoleLogger] [info] [bench.cpp:78] **************************************************************
[2021-11-26 08:30:06.157] [consoleLogger] [info] [bench.cpp:161] basic_st                       Elapsed: 0.10 secs        2,569,305/sec
[2021-11-26 08:30:06.255] [consoleLogger] [info] [bench.cpp:161] basic_st/backtrace-on          Elapsed: 0.10 secs        2,610,360/sec
[2021-11-26 08:30:06.255] [consoleLogger] [info] [bench.cpp:86] 
[2021-11-26 08:30:06.354] [consoleLogger] [info] [bench.cpp:161] rotating_st                    Elapsed: 0.10 secs        2,539,076/sec
[2021-11-26 08:30:06.462] [consoleLogger] [info] [bench.cpp:161] rotating_st/backtrace-on       Elapsed: 0.11 secs        2,320,828/sec
[2021-11-26 08:30:06.462] [consoleLogger] [info] [bench.cpp:93] 
[2021-11-26 08:30:06.572] [consoleLogger] [info] [bench.cpp:161] daily_st                       Elapsed: 0.11 secs        2,271,861/sec
[2021-11-26 08:30:06.699] [consoleLogger] [info] [bench.cpp:161] daily_st/backtrace-on          Elapsed: 0.13 secs        1,977,268/sec
[2021-11-26 08:30:06.699] [consoleLogger] [info] [bench.cpp:100] 
[2021-11-26 08:30:06.716] [consoleLogger] [info] [bench.cpp:161] level-off                      Elapsed: 0.02 secs       14,498,246/sec
[2021-11-26 08:30:06.788] [consoleLogger] [info] [bench.cpp:161] level-off/backtrace-on         Elapsed: 0.07 secs        3,464,112/sec
[2021-11-26 08:30:06.788] [consoleLogger] [info] [bench.cpp:40] **************************************************************
[2021-11-26 08:30:06.788] [consoleLogger] [info] [bench.cpp:41] Multi threaded: 1 threads, 250,000 messages
[2021-11-26 08:30:06.788] [consoleLogger] [info] [bench.cpp:42] **************************************************************
[2021-11-26 08:30:06.893] [consoleLogger] [info] [bench.cpp:192] basic_mt                       Elapsed: 0.10 secs        2,443,554/sec
[2021-11-26 08:30:07.013] [consoleLogger] [info] [bench.cpp:192] basic_mt/backtrace-on          Elapsed: 0.12 secs        2,138,478/sec
[2021-11-26 08:30:07.013] [consoleLogger] [info] [bench.cpp:50] 
[2021-11-26 08:30:07.123] [consoleLogger] [info] [bench.cpp:192] rotating_mt                    Elapsed: 0.11 secs        2,264,899/sec
[2021-11-26 08:30:07.241] [consoleLogger] [info] [bench.cpp:192] rotating_mt/backtrace-on       Elapsed: 0.12 secs        2,133,856/sec
[2021-11-26 08:30:07.241] [consoleLogger] [info] [bench.cpp:57] 
[2021-11-26 08:30:07.362] [consoleLogger] [info] [bench.cpp:192] daily_mt                       Elapsed: 0.12 secs        2,062,364/sec
[2021-11-26 08:30:07.489] [consoleLogger] [info] [bench.cpp:192] daily_mt/backtrace-on          Elapsed: 0.13 secs        1,964,643/sec
[2021-11-26 08:30:07.490] [consoleLogger] [info] [bench.cpp:64] 
[2021-11-26 08:30:07.508] [consoleLogger] [info] [bench.cpp:161] level-off                      Elapsed: 0.02 secs       13,819,593/sec
[2021-11-26 08:30:07.576] [consoleLogger] [info] [bench.cpp:161] level-off/backtrace-on         Elapsed: 0.07 secs        3,681,269/sec
[2021-11-26 08:30:07.576] [consoleLogger] [info] [bench.cpp:40] **************************************************************
[2021-11-26 08:30:07.576] [consoleLogger] [info] [bench.cpp:41] Multi threaded: 4 threads, 250,000 messages
[2021-11-26 08:30:07.576] [consoleLogger] [info] [bench.cpp:42] **************************************************************
[2021-11-26 08:30:07.741] [consoleLogger] [info] [bench.cpp:192] basic_mt                       Elapsed: 0.16 secs        1,545,879/sec
[2021-11-26 08:30:07.917] [consoleLogger] [info] [bench.cpp:192] basic_mt/backtrace-on          Elapsed: 0.17 secs        1,444,630/sec
[2021-11-26 08:30:07.917] [consoleLogger] [info] [bench.cpp:50] 
[2021-11-26 08:30:08.084] [consoleLogger] [info] [bench.cpp:192] rotating_mt                    Elapsed: 0.17 secs        1,495,169/sec
[2021-11-26 08:30:08.264] [consoleLogger] [info] [bench.cpp:192] rotating_mt/backtrace-on       Elapsed: 0.18 secs        1,391,557/sec
[2021-11-26 08:30:08.264] [consoleLogger] [info] [bench.cpp:57] 
[2021-11-26 08:30:08.449] [consoleLogger] [info] [bench.cpp:192] daily_mt                       Elapsed: 0.19 secs        1,350,958/sec
[2021-11-26 08:30:08.655] [consoleLogger] [info] [bench.cpp:192] daily_mt/backtrace-on          Elapsed: 0.21 secs        1,214,701/sec
[2021-11-26 08:30:08.655] [consoleLogger] [info] [bench.cpp:64] 
[2021-11-26 08:30:08.673] [consoleLogger] [info] [bench.cpp:161] level-off                      Elapsed: 0.02 secs       14,321,774/sec
[2021-11-26 08:30:08.743] [consoleLogger] [info] [bench.cpp:161] level-off/backtrace-on         Elapsed: 0.07 secs        3,550,795/sec
08:30:08: /home/shekhar/workspace/core/piModule/logging/build-bench-Desktop_Qt5_12_4-Debug/bench exited with code 0
```
