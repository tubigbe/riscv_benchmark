# Progress Heartbeat

- Current Status: Empirical investigation and benchmark measurements complete. Generating structured report and handoff.
- Last visited: 2026-09-13T00:13:50+01:00
- Completed:
  1. Detailed analysis of run_sim.sh and simulation pipeline.
  2. Verified serv_v1.5_rtl (42-cycle in-window writeback popcount).
  3. Analyzed testbench termination, halt address 0x90000000, and compare_traces.py cycle summing.
  4. Tested and simulated all 3 workloads across both SW and HW modes (6 benchmark runs total).
  5. Cross-referenced existing logs and verified cycle numbers and speedups.
  6. Identified environment nuances (missing host libraries for cc1, snap perl paths, env.sh relative path).
- Next Step: Write comprehensive report.md and handoff.md.
