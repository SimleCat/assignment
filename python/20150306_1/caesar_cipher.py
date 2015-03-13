
def getMessage():
	return \
	'''
	******************************
	* welcome to Caesar`s Cipher *
	******************************
	'''

def getMode():
	mode = None
	while True:
		mode = input("Do you wish to encrypt (e) or decrypt (d) or force(b) a message? \n")
		if mode == "e" or mode == "d" or mode == "b":
			break
	return mode


def getKey():
	key = None
	while True:
		key = input("Enter the key number (1-26): \n")
		if key.isdigit():
			key = int(key)
			if key >= 1 and key <= 26:
				break
	return key

def translateMessage(msg, key, mode):
	# print ("msg: %s, key: %d, mode: %s" % (msg, key, mode))
	if mode == "d": # If mode is decrypt
		key = -key 	# Key becomes negative
	result = ""		# Initialize a variable translated to empty string
	num = 0
	for c in msg: 	# For each symbol in the message
		if c.isalpha(): 	# If the symbol is a letter
			num = ord(c)	# Convert the letter to a number
			num += key 		# Add the key to the number
			if c.isupper(): # If the symbol is upper case
				if num > ord('Z'): 	# If the number is greater than uppercase Z
					num -= 26 		# Subtract 26 from the number	# 
				if num < ord('A'):	# If the number is less than uppercase A
					num += 26 		# Add 26 to the number
			elif c.islower():		# Else if the symbol is lower case
				if num > ord('z'): 	# If the number is greater than lowercase z
					num -= 26 		# Subtract 26 from the number
				if num < ord('a'): 	# If the number is less than lowercase a
					num += 26 		# Add 26 to the number 
			result += chr(num) 		# Convert the number to a character and append it to translated
		else:
			result += c 	# Append the symbol to translated
	return result

def main():
	print (getMessage())
	mode = getMode()
	msg = input("Enter your message: \n")
	if mode != "b":
		key = getKey()
		print ("Your translated text is: ")
		print (translateMessage(msg, key, mode))
	else:
		print ("Out a decrypted version of the phrase with every key from 1 to 26: ")
		for i in range(1, 27):
			print (translateMessage(msg, i, mode))


if __name__ == "__main__":
	main()