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