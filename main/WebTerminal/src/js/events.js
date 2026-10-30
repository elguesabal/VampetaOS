const terminal = document.getElementById("terminal");
const input = document.getElementById("input");
let command = "";
// let history = [];
// let posHistory = 0;

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DE TECLADO PARA SIMULAR A ENTRADA DE COMANDOS NO TERMINAL
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function events(event) {
// console.log(event.key);
	switch (event.key) {
		case "Enter":
			Enter(event);
			break;
		// case "ArrowLeft":
		// 	ArrowLeft(event);
		// 	break;
		// case "ArrowRight":
		// 	ArrowRight(event);
		// 	break;
		case "ArrowUp":
			ArrowUp(event);
			break;
		case "ArrowDown":
			ArrowDown(event);
			break;
		// case "Backspace":
		// 	Backspace(event);
		// 	break;
		// default:
		// 	eventDefault(event);
	}
}

/**
 * @author elguesabal
 * @brief CONTROLA O COMPORTAMENTO DO CLICK NO TERMINAL
*/
function clickTerminal() {
	input.focus();
}

document.addEventListener("keydown", events);
terminal.addEventListener("click", clickTerminal);