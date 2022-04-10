import os

for i in range(30, 40):
	os.system("./Mergesort < Dane3/dane{}.txt".format(i) +" > Wyniki/Mergesort/wyniki{}.txt".format(i))
	os.system("./Quicksort < Dane3/dane{}.txt".format(i) +" > Wyniki/Quicksort/wyniki{}.txt".format(i))
	os.system("./Countingsort < Dane3/dane{}.txt".format(i) +" > Wyniki/Selectionsort/wyniki{}.txt".format(i))