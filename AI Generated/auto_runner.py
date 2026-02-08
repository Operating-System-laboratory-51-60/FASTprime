import subprocess
import matplotlib.pyplot as plt
import os
import sys

# --- Configuration ---
c_source = "solution.c"
executable = "./solution"
start_range = 1000
end_range = 50000
max_cores = 8  # Maximum number of processes to test

# --- Step 1: Compilation ---
print(f"[Python] Compiling {c_source}...")
# compile_cmd: gcc solution.c -o ./solution
compile_cmd = f"gcc {c_source} -o {executable}"
ret_code = os.system(compile_cmd)

if ret_code != 0:
    print("[Error] Compilation failed. Please check gcc installation.")
    sys.exit(1)

# --- Step 2: Benchmarking ---
execution_times = []
# Create a list of process counts: [1, 2, 3, ... max_cores]
process_counts = list(range(1, max_cores + 1))

print(f"[Python] Running benchmarks for range {start_range} to {end_range}...")

for count in process_counts:
    # Construct the command: ./solution 1000 50000 <count>
    cmd = [executable, str(start_range), str(end_range), str(count)]
    
    try:
        # Run the C executable and capture its output (which is just the time)
        output = subprocess.check_output(cmd)
        
        # Decode bytes to string and convert to float
        time_taken = float(output.decode().strip())
        execution_times.append(time_taken)
        
        print(f"  -> Processes: {count} | Time: {time_taken:.4f} seconds")
        
    except subprocess.CalledProcessError as e:
        print(f"[Error] Execution failed for {count} processes.")

# --- Step 3: Visualization ---
print("[Python] Generating plot...")

plt.figure(figsize=(10, 6))
# Plot X (Processes) vs Y (Time)
plt.plot(process_counts, execution_times, marker='o', linestyle='-', color='red', label='AI Solution')

# Add labels and title
plt.title(f"Execution Time vs Number of Processes\nRange: {start_range} - {end_range}")
plt.xlabel("Number of Processes (forks)")
plt.ylabel("Execution Time (seconds)")
plt.grid(True)
plt.legend()

# Save the plot to a file
output_filename = "ai_execution_plot.png"
plt.savefig(output_filename)

print(f"[Success] Plot saved to '{output_filename}'")
print(f"[Success] Prime numbers saved to 'ai_primes.txt'")