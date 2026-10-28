/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA Enter
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function Enter(event) {
	event.preventDefault();
	print("\n");
	// if (command === "") {
	// 	// print("elguesabal@VampetaOS:~$ ");
	// }
	// if (command === "ls") {
	// 	print("a.out  test.c\n");
	// }
// REQUISICAO PARA A API RECEBER O COMANDO
console.log(command)
	command = "";
	print("elguesabal@VampetaOS:~$ ");
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA ArrowLeft
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowLeft(event) {

}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA ArrowRight
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowRight(event) {
	
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA Backspace
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function Backspace(event) {
// console.log(event)
	if (command.length === 0) {
		event.preventDefault();
		return;
	}
	command = command.slice(0, -1);
	document.getElementById("terminal").textContent = document.getElementById("terminal").textContent.slice(0, -1);
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DE TECLAS NAO CONFIGURADAS ANTERIORMENTE
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function eventDefault(event) {
	event.preventDefault();
	if (event.key.length !== 1) return;
	print(event.key);
	command += event.key;
	// cursor++;
}






























// let output = "";
// let command = "";
// let cursor = 0;

// const terminal = document.getElementById("terminal");
// const prompt = "elguesabal@VampetaOS:~$ ";

// function render() {
// 	terminal.replaceChildren();
// 	terminal.appendChild(document.createTextNode(output + prompt + command.slice(0, cursor)));
// 	const cursorElement = document.createElement("span");
// 	cursorElement.id = "cursor";
// 	cursorElement.textContent = command[cursor] ?? " ";
// 	terminal.appendChild(cursorElement);
// 	terminal.appendChild(document.createTextNode(command.slice(cursor + 1)));
// }

// function print(text) {
// 	output += text;
// 	render();
// }

// function events(event) {
// 	switch (event.key) {
// 		case "Enter":
// 			Enter(event);
// 			break;
// 		case "Backspace":
// 			Backspace(event);
// 			break;
// 		case "ArrowLeft":
// 			ArrowLeft(event);
// 			break;
// 		case "ArrowRight":
// 			ArrowRight(event);
// 			break;
// 		default:
// 			eventDefault(event);
// 	}
// }

// document.addEventListener("keydown", events);

// function Enter(event) {
// 	event.preventDefault();
// 	output += prompt + command + "\n";
// // REQUISICAO PARA A API RECEBER O COMANDO
// console.log(command);
// 	command = "";
// 	cursor = 0;
// 	render();
// }

// function ArrowLeft(event) {
// 	event.preventDefault();
// 	if (cursor > 0) {
// 		cursor--;
// 		render();
// 	}
// }

// function ArrowRight(event) {
// 	event.preventDefault();
// 	if (cursor < command.length) {
// 		cursor++;
// 		render();
// 	}
// }

// function Backspace(event) {
// 	event.preventDefault();
// 	if (cursor === 0) return;
// 	command = command.slice(0, cursor - 1) + command.slice(cursor);
// 	cursor--;
// 	render();
// }

// function eventDefault(event) {
// 	if (event.key.length !== 1) return;
// 	if (event.ctrlKey || event.altKey || event.metaKey) return;
// 	command = command.slice(0, cursor) + event.key + command.slice(cursor);
// 	cursor++;
// 	render();
// }

// render();
