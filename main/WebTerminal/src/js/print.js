function print(text) {
	// const line = document.createElement("p");
	// line.textContent = text;
	// document.getElementById("terminal").appendChild(line);



// console.log(text)
	document.getElementById("terminal").textContent += text;
}

print("elguesabal@VampetaOS:~$");

document.addEventListener("keydown", (event) => {
// console.log(event.key);
	// print(event.key);
	switch (event.key) {
		case "Enter":
			// document.getElementById("terminal").textContent += print("\n");
			print("\n");
			break;
		default:
			// document.getElementById("terminal").textContent += print(event.key);
			print(event.key);
	}
});