import numpy as np
import matplotlib.pyplot as plt
import os

# acceptable_keys = ["earth", "sun"]
# acceptable_keys = ["earth", "sun", "jupiter"]
# acceptable_keys = ["earth", "sun", "mars", "jupiter"]
# acceptable_keys = ["sun", "mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune", "pluto"]
acceptable_keys = ["sun", "mercury"]


runname = "run1"
runname = "relativistic_run"

data = {}
print("Retrieving objects from 'data/':")
for filename in os.listdir("data"):
    if filename.startswith(".") or filename.startswith("_"):
        continue

    if not runname in filename:
        continue

    filepath = os.path.join("data", filename)

    for obj_name in acceptable_keys:
        if obj_name in filepath:
            object_name = obj_name
            break
    else:
        continue


    print(object_name.capitalize(), "at", filepath)

    # Old method
    # x, y, z, vx, vy, vz, Lx, Ly, Lz, KE, PE = np.loadtxt(filepath).T

    # New method
    bin_data = np.fromfile(filepath, dtype=np.float64)

    N = int(bin_data.shape[0] / 11)

    x, y, z = bin_data[:3*N].reshape((N,3)).T
    vx, vy, vz = bin_data[3*N: 3*N*2].reshape((N,3)).T
    Lx, Ly, Lz = bin_data[3*N*2: 3*N*3].reshape((N,3)).T
    KE = bin_data[3*N*3: 10*N]
    PE = bin_data[10*N:]

    # print (x[0], y[0], z[0])

    object_data = {
        "pos": np.array((x, y, z)),
        "vel": np.array((vx, vy, vz)),
        "angmom": np.array((Lx, Ly, Lz)),
        "kinetic_energy": KE,
        "potential_energy": PE,
    }
    data[object_name] = object_data

if len(data.values())==0:
    raise IOError("No data found for run: {}".format(runname))

# # Summing total energy
# total_kinetic_energy = []
# total_potential_energy = []
# total_energy = []
# total_angular_momentum = []
# for key in data:
#     total_kinetic_energy.append(data[key]["kinetic_energy"])
#     total_potential_energy.append(data[key]["potential_energy"])
#     total_energy.append(
#         data[key]["kinetic_energy"] + data[key]["potential_energy"])
#     total_angular_momentum.append(data[key]["angmom"])

# total_kinetic_energy = np.asarray(total_kinetic_energy).sum(axis=0)
# total_potential_energy = np.asarray(total_potential_energy).sum(axis=0)
# total_energy = np.asarray(total_energy).sum(axis=0)
# total_angular_momentum = np.linalg.norm(np.asarray(total_angular_momentum).sum(axis=0), axis=0)

# Mercury precession
# Selects closest approach values
data_sun = data["sun"]["pos"]
data_mercury = data["mercury"]["pos"]
distances = np.linalg.norm(data_sun - data_mercury, axis=0)

xy_closest_approach = [[0, distances[0]]]

xy_cords = []
mercury_perihelions = []

for i in range(1, data_sun.shape[1]-1):
    if (distances[i-1] > distances[i]) and (distances[i+1] > distances[i]):
        xy_closest_approach.append([i, distances[i]])
        xy_cords.append(data_sun[:,i] - data_mercury[:,i])
        mercury_perihelions.append(data_mercury[:,i])

xy_cords = np.asarray(xy_cords)
mercury_perihelions = np.asarray(mercury_perihelions)

# print(xy_cords.shape)
# print(xy_closest_approach)

theta = np.arctan2(xy_cords[:,1], xy_cords[:,0])#*180 / np.pi * (3600)

# print ((theta[-1] - theta[0])*180/np.pi*3600)
x_mins = []
theta_mins = []

# for i in range(1, len(theta)-1):
#     if (theta[i-1] > theta[i]) and (theta[i+1] > theta[i]):
#         theta_mins.append(theta[i])
#         x_mins.append(i)
# print (theta_mins[0] - theta_mins[-1])

print (np.abs(theta[0] - theta[-1]) * 180/np.pi*3600)
print(mercury_perihelions[0,0], mercury_perihelions[0,1])
print(mercury_perihelions[-1,0], mercury_perihelions[-1,1])

plt.plot(data["mercury"]["pos"][0], data["mercury"]["pos"][1], label="Mercury", zorder=1)
plt.plot(mercury_perihelions[:,0], mercury_perihelions[:,1], "o", label="Mercury perhihelions", zorder=2)
plt.scatter(mercury_perihelions[0,0], mercury_perihelions[0,1], label=r"$i=0$", color="#145A46FF", zorder=3)
plt.scatter(mercury_perihelions[-1,0], mercury_perihelions[-1,1], label=r"$i=100$", color="#145A46FF", zorder=3)

i_y_min = np.argmin(mercury_perihelions[:,1])
i_y_max = np.argmax(mercury_perihelions[:,1])
plt.scatter(mercury_perihelions[i_y_min,0], mercury_perihelions[i_y_min,1], label=r"$i={}$".format(i_y_min), color="#74D723FF", zorder=3)
plt.scatter(mercury_perihelions[i_y_max,0], mercury_perihelions[i_y_max,1], label=r"$i={}$".format(i_y_max), color="#74D723FF", zorder=3)


print((np.abs(np.arctan(mercury_perihelions[0,1]/mercury_perihelions[0,0]) - np.arctan(mercury_perihelions[-1,1]/mercury_perihelions[-1,0])))*180/np.pi*3600)
print((np.abs(np.arctan(mercury_perihelions[i_y_min,1]/mercury_perihelions[i_y_min,0]) - np.arctan(mercury_perihelions[i_y_max,1]/mercury_perihelions[i_y_max,0])))*180/np.pi*3600)

plt.legend()
plt.show()

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