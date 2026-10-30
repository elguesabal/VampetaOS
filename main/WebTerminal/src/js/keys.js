/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA Enter
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function Enter(event) {
	event.preventDefault();
	print(input.textContent + "\n");
// history.push(input.textContent);
// posHistory++;
	input.textContent = "";
	// if (command === "") {
	//	print("elguesabal@VampetaOS:~$ ");
	// }
	// if (command === "ls") {
	// 	print("a.out  test.c\n");
	// }
// REQUISICAO PARA A API RECEBER O COMANDO
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
 * @brief TRATA EVENTOS DA TECLA ArrowUp
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowUp(event) {
	event.preventDefault();
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA ArrowDown
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function ArrowDown(event) {
	event.preventDefault();
}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DA TECLA Backspace
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function Backspace(event) {

}

/**
 * @author elguesabal
 * @brief TRATA EVENTOS DE TECLAS NAO CONFIGURADAS ANTERIORMENTE
 * @param event OBJETO CONTENDO AS INFORMACOES DO EVENTO DE TECLADO
*/
function eventDefault(event) {

}