import subprocess

count = 0

while True:
    print("*************************")
    print(count)
    count += 1
    print("*************************")

    result = subprocess.run(["make", "run"])
    if count > 1000000:
        print("done 1000000 times")
        break