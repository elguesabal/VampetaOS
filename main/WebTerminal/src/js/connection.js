/**
 * @author elguesabal
 * @brief FUNCAO DE NOTIFICACAO DE CONEXAO DO WEBSOCKET
 * @param event OBJETO CONTENDO INFORMACOES SOBRE A ABERTURA DA CONEXAO WEBSOCKET
*/
function onopen(event) {

}

/**
 * @author elguesabal
 * @brief FUNCAO QUE RECEBE AS MENSAGENS DO WEBSOCKET
 * @param event OBJETO CONTENDO INFORMACOES SOBRE RECEBIMENTO DA MENSAGEM
*/
function onmessage(event) {
	try {
		const data = JSON.parse(event.data);
		if (data.type === "OUTPUT") {
			print(data.output);
		} else if (data.type === "INPUT") {
			print(data.output);
		} else if (data.type === "FINISHED") {
			print(data.output);
		}
	} catch (error) {
		print("Invalid response\n");
		print("elguesabal@VampetaOS:~$ ");
	}
}

/**
 * @author elguesabal
 * @brief FUNCAO QUE RECEBE ERROS SOBRE A CONEXAO DO WEBSOCKET
 * @param event OBJETO CONTENDO INFORMACOES SOBRE ERROS OCORRIDOS NA CONEXAO
*/
function onerror(event) {

}

/**
 * @author elguesabal
 * @brief FUNCAO DE NOTIFICACAO DE FECHAMENTO DA CONEXAO WEBSOCKET
 * @param event OBJETO CONTENDO INFORMACOES SOBRE O FECHAMENTO DA CONEXAO
*/
function onclose(event) {
	
}

ws.onopen = onopen;
ws.onmessage = onmessage;
ws.onerror = onerror;
ws.onclose = onclose;