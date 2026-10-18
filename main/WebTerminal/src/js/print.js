function print(text) {
	const line = document.createElement("p");
	line.textContent = text;
	document.getElementById("terminal").appendChild(line);
}

print("elguesabal@VampetaOS:~$");