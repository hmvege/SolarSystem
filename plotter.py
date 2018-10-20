import numpy as np
import matplotlib.pyplot as plt
import os

acceptable_keys = ["earth", "sun"]
# acceptable_keys = ["earth", "sun", "jupiter"]
# acceptable_keys = ["earth", "sun", "mars", "jupiter"]
acceptable_keys = ["sun", "mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune", "pluto"]
# acceptable_keys = ["mercury"]


data = {}
print("Retrieving objects from 'data/':")
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
        "potential_energy": PE,
    }
    data[object_name] = object_data

# Summing total energy
total_kinetic_energy = []
total_potential_energy = []
total_energy = []
total_angular_momentum = []
for key in data:
    total_kinetic_energy.append(data[key]["kinetic_energy"])
    total_potential_energy.append(data[key]["potential_energy"])
    total_energy.append(
        data[key]["kinetic_energy"] + data[key]["potential_energy"])
    total_angular_momentum.append(data[key]["angmom"])

total_kinetic_energy = np.asarray(total_kinetic_energy).sum(axis=0)
total_potential_energy = np.asarray(total_potential_energy).sum(axis=0)
total_energy = np.asarray(total_energy).sum(axis=0)
total_angular_momentum = np.linalg.norm(np.asarray(total_angular_momentum).sum(axis=0), axis=0)

# # Mercury precession
# theta = np.arctan(data["mercury"]["pos"][1]/data["mercury"]["pos"][0])*180 / np.pi / 60 / 60
# theta_max = theta[np.where((theta > 0.024))]
# plt.plot(theta_max)
# plt.show()

# # Plots planets
# for key in data:
#     if key in acceptable_keys:
#         print("Plotting {}".format(key.capitalize()))
#         plt.plot(data[key]["pos"][0], data[key]["pos"][1], 
#            label=key.capitalize())
# max_axis = max([np.max(np.abs(data[k]["pos"])) for k in data])
# max_axis *= 1.5
# plt.axis("equal")
# plt.grid(True)
# plt.xlim(-max_axis, max_axis)
# plt.ylim(-max_axis, max_axis)
# plt.legend()
# plt.show()

# # Energy plot
# plt.plot(total_kinetic_energy, label="Kinetic energy")
# plt.plot(total_potential_energy, label="Potential energy")
# plt.plot(total_energy, label="Total energy")
# plt.legend()
# plt.show()

# Angular momentum
# print ("Plotting total angular momentum")
# plt.plot(total_angular_momentum, label="Angular momentum")
# plt.legend()
# plt.show()