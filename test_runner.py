import os
import subprocess
import sys
import tempfile
import re
import csv

MYSHELL = os.path.abspath("mysh")
REFER = "/bin/tcsh -f"
TRAPSIG = False
TESTS_FILE = "tests"
CSV_FILE = "test_results.csv"

def reset_csv():
    """Réinitialise le fichier CSV des résultats des tests."""
    with open(CSV_FILE, "w", newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["Test ID", "Test Name", "Result", "Expected Output", "Actual Output"])

def read_tests():
    """Lit le fichier de tests et retourne un dictionnaire des tests."""
    tests = {}
    with open(TESTS_FILE, "r") as f:
        content = f.read()
    matches = re.findall(r"\[(\d+)](.*?)\[\1-END]", content, re.DOTALL)

    for test_id, test_content in matches:
        test_data = parse_test(test_content.strip())
        tests[test_id] = test_data

    return tests

def parse_test(test_content):
    """Analyse un bloc de test et retourne un dictionnaire des paramètres du test."""
    test_data = {}
    lines = test_content.split("\n")

    for line in lines:
        if "=" in line:
            key, value = line.split("=", 1)
            test_data[key.strip()] = value.strip().strip('"')

    test_data["TESTS"] = [line.strip() for line in lines if "echo" in line]
    return test_data

def prepare_script(test_data):
    """Crée un script temporaire pour exécuter le test."""
    script_fd, script_path = tempfile.mkstemp(suffix=".sh")
    runner_fd, runner_path = tempfile.mkstemp(suffix=".sh")

    with os.fdopen(script_fd, "w") as script_file:
        script_file.write("#!/bin/bash\n")
        script_file.write(f"{test_data.get('SETUP', '')}\n")
        for test in test_data["TESTS"]:
            if "<<" in test:
                script_file.write(f"{test}\nEOF\n")  # Assure que EOF est bien placé
            else:
                script_file.write(f"{test}\n")
    with os.fdopen(runner_fd, "w") as runner_file:
        runner_file.write("#!/bin/bash\n")
        runner_file.write(f"source {script_path} | {MYSHELL} > {script_path}.out 2>&1\n")
        runner_file.write(f"source {script_path} | {REFER} > {script_path}.ref 2>&1\n")

    os.chmod(script_path, 0o755)
    os.chmod(runner_path, 0o755)

    return script_path, runner_path

def run_test(test_id, test_data, debug=False):
    """Exécute un test et compare les résultats."""
    script_path, runner_path = prepare_script(test_data)
    subprocess.run([runner_path], shell=True)

    shell_output = read_file(script_path + ".out")
    refer_output = read_file(script_path + ".ref")

    result = "OK" if shell_output == refer_output else "KO"
    color = "\033[92m" if result == "OK" else "\033[91m"

    print(f"{color}Test {test_id} ({test_data.get('NAME', 'Unknown')}) : {result}\033[0m")
    if result == "KO":
        save_debug_info(test_id, shell_output, refer_output)

    update_csv(test_id, test_data.get('NAME', 'Unknown'), result, refer_output, shell_output)
    cleanup(script_path, runner_path)

    return result

def update_csv(test_id, test_name, result, expected_output, actual_output):
    """Met à jour le fichier CSV avec les résultats du test."""
    with open(CSV_FILE, "a", newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow([test_id, test_name, result, expected_output, actual_output])

def read_file(file_path):
    """Lit un fichier et retourne son contenu."""
    try:
        with open(file_path, "r") as f:
            return f.read().strip()
    except FileNotFoundError:
        return ""

def save_debug_info(test_id, shell_output, refer_output):
    """Sauvegarde les sorties de test en cas d'échec."""
    debug_path = f"/tmp/test_debug/{test_id}"
    os.makedirs(debug_path, exist_ok=True)

    with open(f"{debug_path}/mysh.out", "w") as f:
        f.write(shell_output)

    with open(f"{debug_path}/tcsh.out", "w") as f:
        f.write(refer_output)

    print(f"Check output in {debug_path}/")

def cleanup(*file_paths):
    """Supprime les fichiers temporaires."""
    for file_path in file_paths:
        try:
            os.remove(file_path)
        except OSError:
            pass

def main():
    """Exécute tous les tests ou un test spécifique."""
    reset_csv()
    ok_count = 0
    ko_count = 0

    if not os.path.exists(TESTS_FILE):
        print("No tests file. Please read README.md", file=sys.stderr)
        sys.exit(1)

    if not os.path.exists(MYSHELL):
        print(f"{MYSHELL} not found", file=sys.stderr)
        sys.exit(1)

    tests = read_tests()

    if len(sys.argv) == 2:
        result = run_test(sys.argv[1], tests.get(sys.argv[1], {}), debug=True)
        if result == "OK":
            ok_count += 1
        else:
            ko_count += 1
    else:
        for test_id, test_data in tests.items():
            result = run_test(test_id, test_data)
            if result == "OK":
                ok_count += 1
            else:
                ko_count += 1

    print(f"\033[92mTests réussis : {ok_count}\033[0m")
    print(f"\033[91mTests échoués : {ko_count}\033[0m")

if __name__ == "__main__":
    main()