import matplotlib.pyplot as plt

# ------------------ SIMULATION DATA ------------------
# Replace these lists with your Tinkercad readings
time_sec = list(range(0, 60, 5))  # time in seconds
temperature = [25, 28, 36, 35, 38, 40, 47, 49, 46, 42, 38, 35]  # °C
gas = [85, 100, 120, 140, 130, 120, 135, 155, 180, 200, 240, 340]  # analog values
heart_rate = [60, 50, 40, 50, 65, 75, 82, 90, 92, 88, 80, 75]  # bpm

# ------------------ ALERT THRESHOLDS ------------------
TEMP_HIGH_ALERT = 40
TEMP_LOW_ALERT  = 10
GAS_ALERT       = 150
HEART_LOW       = 50
HEART_HIGH      = 125

# ------------------ PLOT SETUP ------------------
fig, ax1 = plt.subplots(figsize=(12, 6))

# Temperature plot
ax1.plot(time_sec, temperature, 'r-o', label='Temperature (°C)')
ax1.set_xlabel('Time (sec)')
ax1.set_ylabel('Temperature (°C)', color='r')
ax1.tick_params(axis='y', labelcolor='r')
ax1.set_ylim(0, 60)

# Highlight temperature alert zones
ax1.fill_between(time_sec, TEMP_HIGH_ALERT, 60, color='red', alpha=0.2)
ax1.fill_between(time_sec, 0, TEMP_LOW_ALERT, color='blue', alpha=0.2)

# Second y-axis for Gas and Heart Rate
ax2 = ax1.twinx()
ax2.plot(time_sec, gas, 'g-s', label='Gas Level')
ax2.plot(time_sec, heart_rate, 'b-^', label='Heart Rate')
ax2.set_ylabel('Gas / Heart Rate', color='b')
ax2.tick_params(axis='y', labelcolor='b')
ax2.set_ylim(0, 500)

# Highlight gas alert zone
ax2.fill_between(time_sec, GAS_ALERT, 500, color='orange', alpha=0.2)

# Highlight heart rate alert zones
ax2.fill_between(time_sec, 0, HEART_LOW, color='purple', alpha=0.1)
ax2.fill_between(time_sec, HEART_HIGH, 200, color='purple', alpha=0.1)

# Legends and title
fig.legend(loc='upper left', bbox_to_anchor=(0.1, 0.9))
plt.title('Soldier Monitoring with Alerts')
ax1.grid(True)

# Show plot
plt.show()
