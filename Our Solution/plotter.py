import sys
import matplotlib.pyplot as plt
import subprocess

def run_benchmark(user_start, user_end, max_cores):
    ranges_to_test = [
        {"label": f"User Input ({user_start}-{user_end})", "start": user_start, "end": user_end},
        {"label": "Small Load (1k-10k)",   "start": 1000,   "end": 10000},
        {"label": "Medium Load (10k-50k)", "start": 10000,  "end": 50000},
        {"label": "Heavy Load (50k-150k)", "start": 50000,  "end": 150000}
    ]

    cores_list = list(range(1, max_cores + 1))
    
    plt.figure(figsize=(12, 8))

    for config in ranges_to_test:
        start = config["start"]
        end = config["end"]
        label = config["label"]
        times = []

        print(f"\n[Graphing] Benchmarking: {label}...")

        # Run the C executable for 1..N cores
        for c in cores_list:
            try:
                cmd = ["./prime_app", str(start), str(end), str(c)]
                result = subprocess.check_output(cmd)
                
                time_taken = float(result.decode().strip())
                times.append(time_taken)
                
                sys.stdout.write(f"\r  -> Cores: {c}/{max_cores} | Time: {time_taken:.4f}s")
                sys.stdout.flush()
            except Exception as e:
                print(f"\n  [Error] Failed on {label} with {c} cores.")
                times.append(None)
        if None not in times:
            plt.plot(cores_list, times, marker='o', linestyle='-', linewidth=2, label=label)

    print("\n\n[Graphing] Saving Comparison Plot...")

    plt.title(f"Performance Comparison: Multi-Process Prime Calculation\n(User Range vs Standard Workloads)")
    plt.xlabel("Number of Processes (CPU Cores)")
    plt.ylabel("Execution Time (seconds)")
    plt.grid(True, which='both', linestyle='--', linewidth=0.5)
    plt.legend()
    
    filename = "multi_range_comparison.png"
    plt.savefig(filename)
    print(f"[Success] Saved: {filename}")

if __name__ == "_main_":
    if len(sys.argv) < 4:
        run_benchmark(1000, 5000, 4)
    else:
        run_benchmark(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))