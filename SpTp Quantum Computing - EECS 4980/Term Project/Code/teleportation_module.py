# teleportation_module.py

# import the necessary libraries
from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector, partial_trace, state_fidelity, DensityMatrix
from qiskit_ibm_runtime import QiskitRuntimeService, SamplerV2
from qiskit import transpile

#===Input state preparation===#
def prep_zero(qc: QuantumCircuit):
	'''Prepares the input state |0>'''
	pass

def prep_one(qc: QuantumCircuit):
	'''Prepares the input state |1>'''
	qc.x(0)

def prep_plus(qc: QuantumCircuit):
	'''Prepares the input state |+> = (|0> + |1>)/sqrt(2)'''
	qc.h(0)

def prep_minus(qc: QuantumCircuit):
	'''Prepares the input state |-> = (|0> - |1>)/sqrt(2)'''
	qc.x(0)
	qc.h(0)

#============================#
# TELEPORTAION CIRCUIT IDEAL #
#============================#
def build_teleportation_circuit(prepare_input_state):
	'''
	Create a 3-qubit teleportation circuit using coherent correction unitaries.
	q0: input qubit
	q1: Alice's entangled qubit
	q2: Bob's entangled qubit
	'''
	qc = QuantumCircuit(3)

	# Prepare input |psi> on q0
	prepare_input_state(qc)

	# Create Bell pair between q1 and q2
	qc.h(1)
	qc.cx(1, 2)

	# Bell measurement (as unitaries)
	qc.cx(0, 1)
	qc.h(0)

	# *** REQUIRED UNITARIES FOR PERFECT TELEPORTATION ***
	qc.cx(1, 2)  # X correction
	qc.cz(0, 2)  # Z correction

	return qc

def teleport_and_get_bob_state(prepare_input_state):
	'''
	Performs the quantum teleportation protocol and returns the state of Bob's qubit after the protocol is finished.
	'''
	qc = build_teleportation_circuit(prepare_input_state)

	# Final statevector of the full 3-qubit system
	psi = Statevector.from_instruction(qc)

	# Trace out q0 and q1 to isolate Bob's qubit
	rho_bob = partial_trace(psi, [0, 1])
	return rho_bob

def get_ideal_state(prepare_input_state):
	'''
	Returns the ideal state that the teleportation protocol should output.
	'''
	qc = QuantumCircuit(1)
	prepare_input_state(qc)
	return Statevector.from_instruction(qc)

def teleportation_fidelity(prepare_input_state):
	'''
	Computes the fidelity of the teleportation protocol with respect to the ideal state.
	'''
	rho_bob = teleport_and_get_bob_state(prepare_input_state)
	psi_ideal = get_ideal_state(prepare_input_state)
	return state_fidelity(rho_bob, psi_ideal)


#============================#
# HARDWARE CIRCUIT EXECUTION #
#============================#
def build_hardware_circuit(prepare_input_state):
	'''
	Builds the teleportation circuit with measurements for execution on IBM hardware.
	'''
	qc = build_teleportation_circuit(prepare_input_state)
	qc.measure_all()
	return qc

def run_on_hardware(prepare_input_state, shots=4096):
	'''
	Executes the teleportation circuit on an IBM quantum processor.  
	NOTE: Requires a configured IBM Quantum account.
	'''
	try:
		service = QiskitRuntimeService()
	except Exception as e:
		print("IBM account not configured:", e)
		return None

	# Try preferred real backend first
	preferred_backends = ["ibm_fez", "ibm_oslo", "ibm_quito"]

	backend = None
	for name in preferred_backends:
		try:
			backend = service.backend(name)
			print(f"Using backend: {name}")
			break
		except:
			continue

	# If no hardware is available, use noisy simulator
	if backend is None:
		print("No real hardware available. Using noisy simulator instead.")
		backend = service.backend("ibm_sherbrooke_simulator")

	qc = build_hardware_circuit(prepare_input_state)

	# Transpile for the backend
	qc = transpile(qc, backend)

	# Initialize SamplerV2 with backend
	sampler = SamplerV2(backend)

	# Run circuit
	job = sampler.run([qc], shots=shots)

	# Get results
	result = job.result()

	data = result[0].data

	if "meas" in data:
		counts = data["meas"].get_counts()
	else:
		raise KeyError("No measurement data returned")

	return counts


def fidelity_from_counts(counts, ideal_state):
	'''
	Approximates fidelity using hardware measurement results.
	Extracts probabilities of measuring Bob's qubit as '0' or '1'.
	'''
	shots = sum(counts.values())
	probs = {k: v / shots for k, v in counts.items()}

	# Extract Bob's qubit (the LAST bit in a bitstring)
	p0 = sum(v for k, v in probs.items() if k[-1] == '0')
	p1 = sum(v for k, v in probs.items() if k[-1] == '1')

	# Build approximate density matrix
	rho = DensityMatrix([[p0, 0], [0, p1]])

	return state_fidelity(rho, ideal_state)