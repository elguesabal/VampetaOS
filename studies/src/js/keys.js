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
	cursor = 0;
	print("elguesabal@VampetaOS:~$ ");
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA ArrowLeft
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowLeft(event) {
	if (command.length === cursor) {
		event.preventDefault();
		return;
	}
	cursor++;
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA ArrowRight
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowRight(event) {
	if (cursor === 0) {
		event.preventDefault();
		return;
	}
	cursor--;
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA Backspace
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function Backspace(event) {
	if (command.length === 0 || cursor === command.length) {
		event.preventDefault();
		return;
	}
	command = command.substring(0, command.length - cursor - 1) + command.substring(command.length - cursor);
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
}