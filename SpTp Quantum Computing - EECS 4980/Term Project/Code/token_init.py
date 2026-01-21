from qiskit_ibm_runtime import QiskitRuntimeService

QiskitRuntimeService.delete_account()

with open("qiskit_token.txt") as f:
	token = f.read().strip()

QiskitRuntimeService.save_account(channel="ibm_quantum_platform", token=token)
