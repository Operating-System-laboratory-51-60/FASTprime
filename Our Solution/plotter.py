import sys
import matplotlib.pyplot as plt
import subprocess

def run_benchmark(start, end, max_cores):
    cores_list = list(range(1, max_cores + 1))
    times = []

    print(f"\n[Graphing] Running benchmarks for range {start}-{end}...")
    
    for c in cores_list:
        # Call the C modular executable
        result = subprocess.check_output(["./prime_app", str(start), str(end), str(c)])
        time_taken = float(result.decode().strip())
        times.append(time_taken)
        # Progress bar UI
        sys.stdout.write(f"\r Progress: [{'#' * c}{'.' * (max_cores - c)}] {c}/{max_cores} cores")
        sys.stdout.flush()

    print("\n[Graphing] Generating plot...")
    plt.figure()
    plt.plot(cores_list, times, marker='o', linestyle='-', color='b')
    plt.title(f"Execution Time vs Cores (Range: {start}-{end})")
    plt.xlabel("Number of Processes")
    plt.ylabel("Time (seconds)")
    plt.grid(True)
    plt.savefig(f"benchmark_{start}_{end}.png")
    print(f"[Success] Saved: benchmark_{start}_{end}.png")

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python3 plotter.py <start> <end> <max_cores>")
        sys.exit(1)
    run_benchmark(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))