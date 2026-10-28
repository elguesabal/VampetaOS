let command = "";
let cursor = 0;

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DE TECLADO PARA SIMULAR A ENTRADA DE COMANDOS NO TERMINAL
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function events(event) {
console.log(event.key);
	switch (event.key) {
		case "Enter":
			Enter(event);
			break;
		case "ArrowLeft":
			ArrowLeft(event);
			break;
		case "ArrowRight":
			ArrowRight(event);
			break;
		case "Backspace":
			Backspace(event);
			break;
		default:
			eventDefault(event);
	}
}

/**
 * @author elguesabal
 * @brief CONTROLA O COMPORTAMENTO DO CLICK NO TERMINAL
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DO MOUSE
*/
function clickTerminal(event) {
	// event.preventDefault();
	// document.getElementById("terminal").focus();
	// event.currentTarget.focus();
}

document.addEventListener("keydown", events);
document.getElementById("terminal").addEventListener("mousedown", clickTerminal);