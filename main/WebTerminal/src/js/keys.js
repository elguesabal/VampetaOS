/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA Enter
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function Enter(event) {
	event.preventDefault();
	print(input.textContent + "\n");
	if (input.textContent === "") {
		input.textContent = "";
		print("elguesabal@VampetaOS:~$ ");
		return;
	}
	history.push(input.textContent);
	posHistory = history.length;
// if (input.textContent === "ls") {
// 	print("a.out  test.c\n");
// }
	if (input.textContent === "clear") {
		terminal.replaceChildren(input);
		input.textContent = "";
		print("elguesabal@VampetaOS:~$ ");
		input.focus();
		return;
	}
// REQUISICAO PARA A API RECEBER O COMANDO
if (ws.readyState === WebSocket.OPEN) {
	ws.send(input.textContent);
	input.textContent = "";
// console.log("foi")
	return;
} else {
// console.log("ERROR")
	// print("ERROR");
}
	input.textContent = "";
	print("elguesabal@VampetaOS:~$ ");
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