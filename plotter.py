import numpy as np
import matplotlib.pyplot as plt
import os

# acceptable_keys = ["earth", "sun"]#, "mars", "jupiter"]
acceptable_keys = ["mercury"]


data = {}
print("Retrieving objects from data/ :")
for filename in os.listdir("data"):
    if filename.startswith(".") or filename.startswith("_"):
        continue

    filepath = os.path.join("data", filename)

    object_name = filename.split("_")[1]

    if not object_name in acceptable_keys:
        continue

    print(object_name.capitalize())

    x, y, z, vx, vy, vz, Lx, Ly, Lz, KE, PE = np.loadtxt(filepath).T

    object_data = {
        "pos": np.array((x, y, z)),
        "vel": np.array((vx, vy, vz)),
        "angmom": np.array((Lx, Ly, Lz)),
        "kinetic_energy": KE,
        "potentail_energy": PE,
    }
    data[object_name] = object_data

# Summing total energy
total_energy = []
for key in data:
    data[key]["kinetic_energy"]
    data[key]["potentail_energy"]

for key in data:
    if key in acceptable_keys:
        print("Plotting {}".format(key.capitalize()))
        plt.plot(data[key]["pos"][0], data[key]["pos"][1], label=key)

max_axis = max([np.max(np.abs(data[k]["pos"])) for k in data])
max_axis *= 1.5

# # Mercury precession
# theta = np.arctan(data["mercury"]["pos"][1]/data["mercury"]["pos"][0])*180 / np.pi / 60 / 60
# theta_max = theta[np.where((theta > 0.024))]
# plt.plot(theta_max)
# plt.show()

plt.axis("equal")
plt.grid(True)
plt.xlim(-max_axis, max_axis)
plt.ylim(-max_axis, max_axis)
plt.legend()
plt.show()
