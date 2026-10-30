/**
 * @author elguesabal
 * @brief FUNCAO QUE INSERE UM TEXTO AO TERMINAL
 * @param text TEXTO QUE SERA INSERIDO NO TERMINAL
*/
function print(text) {
	document.getElementById("terminal").textContent += text;
}

print("elguesabal@VampetaOS:~$ ");