/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA Enter
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function Enter(event) {
	event.preventDefault();
	const command = input.textContent;	// DEVERIA ME PREOCUPAR COM CARACTERES DE SCAPE
	print(command + "\n");
	input.textContent = "";
	if (command === "") {
		print("elguesabal@VampetaOS:~$ ");
		return;
	}
	history.push(command);
	posHistory = history.length;
	if (command === "clear") {
		terminal.replaceChildren(input);
		print("elguesabal@VampetaOS:~$ ");
		input.focus();
		return;
	}
	if (ws.readyState !== WebSocket.OPEN) {
		print("WebSocket: connection unavailable\n");
		print("elguesabal@VampetaOS:~$ ");
		return;
	}
	ws.send(command);
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA ArrowUp
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowUp(event) {
	event.preventDefault();
	if (history.length === 0) return;
	if (posHistory === history.length) currentCommand = input.textContent;
	if (posHistory === 0) return;
	posHistory--;
	input.textContent = history[posHistory];
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA ArrowDown
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowDown(event) {
	event.preventDefault();
	if (posHistory >= history.length) return;
	posHistory++;
	if (posHistory === history.length) {
		input.textContent = currentCommand;
		return;
	}
	input.textContent = history[posHistory];
}