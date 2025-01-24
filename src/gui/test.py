for a in range(8,20,4):
	for b in range(1,4):
		if a % b >= b / 3:
			if a / 4 <= b + 1:
				print("Homer")
			else:
				print("Marge")
		else:
			print("Bart")
