ws.onopen = (event) => {
	console.log("onopen:", event);
};

ws.onmessage = (event) => {
	console.log("onmessage:", event);
	print(event.data);
print("elguesabal@VampetaOS:~$ ");
};

ws.onerror = (event) => {
	console.log("onerror:", event);
};

ws.onclose = (event) => {
	console.log("onclose:", event);
};