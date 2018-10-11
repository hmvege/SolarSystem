import numpy as np
import matplotlib.pyplot as plt
import os

data = {}
for filename in os.listdir("data"):
    if filename.startswith(".") or filename.startswith("_"):
        continue

    filepath = os.path.join("data", filename)

    object_name = filename.split("_")[0]
    print(object_name.capitalize())

    x, y, z, vx, vy, vz = np.loadtxt(filepath).T

    object_data = {
        "pos": np.array((x, y, z)),
        "vel": np.array((vx, vy, vz)),
    }
    data[object_name] = object_data

print( data["earth"]["pos"][0][0])


for key in data:
    print ("Plotting {}".format(key.capitalize()))
    plt.plot(data[key]["pos"][0], data[key]["pos"][1], label=key)
    
plt.axis("equal")
plt.grid(True)
plt.xlim(-4,4)
plt.ylim(-4,4)
plt.legend()
plt.show()