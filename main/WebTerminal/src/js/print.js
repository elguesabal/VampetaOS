/**
 * @author elguesabal
 * @brief FUNCAO QUE INSERE UM TEXTO AO TERMINAL
 * @param text TEXTO QUE SERA INSERIDO NO TERMINAL
*/
function print(text) {
	const element = document.createElement("span");
	element.textContent = text;
	terminal.insertBefore(element, document.getElementById("input"));
}

print("elguesabal@VampetaOS:~$ ");





// const ws = new WebSocket(`ws://${window.location.host}/webterminal`);

// ws.onopen = () => {
// 	console.log("WebSocket: Connected");
// };

// ws.onmessage = (event) => {
// 	console.log("Server:", event.data);
// };

// ws.onerror = (error) => {
// 	console.error("WebSocket Error:", error);
// };

// ws.onclose = () => {
// 	console.log("WebSocket: Disconnected");
// };