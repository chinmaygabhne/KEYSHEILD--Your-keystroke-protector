import tkinter as tk
from tkinter import messagebox, ttk

class KeyShieldGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("KeyShield: Behavioral Monitor")
        self.root.geometry("760x420")

        columns = ("pid", "process_name", "threat_score", "status")
        self.tree = ttk.Treeview(root, columns=columns, show="headings")
        self.tree.heading("pid", text="PID")
        self.tree.heading("process_name", text="Process Name")
        self.tree.heading("threat_score", text="Threat Score")
        self.tree.heading("status", text="Status")
        self.tree.column("pid", width=90, anchor=tk.CENTER)
        self.tree.column("process_name", width=280, anchor=tk.W)
        self.tree.column("threat_score", width=120, anchor=tk.CENTER)
        self.tree.column("status", width=140, anchor=tk.CENTER)
        self.tree.pack(fill=tk.BOTH, expand=True)

        self.populate_mock_data()

        self.btn = tk.Button(
            root,
            text="Isolate High Threats",
            command=self.mitigate,
            bg="red",
            fg="white",
        )
        self.btn.pack(pady=20)

    def populate_mock_data(self):
        rows = (
            ("4042", "explorer.exe", 0, "Trusted"),
            ("8120", "unknown_logger.exe", 85, "Active threat"),
            ("9216", "macro_tool.exe", 55, "Under review"),
        )
        for row in rows:
            self.tree.insert("", "end", values=row)

    def mitigate(self):
        mitigated = []
        for item_id in self.tree.get_children():
            values = list(self.tree.item(item_id, "values"))
            threat_score = int(values[2])
            if threat_score >= 70:
                values[3] = "Isolated"
                self.tree.item(item_id, values=values)
                mitigated.append(f"PID {values[0]} ({values[1]})")

        if mitigated:
            messagebox.showinfo(
                "Mitigation complete",
                "Isolated high-threat processes:\n" + "\n".join(mitigated),
            )
        else:
            messagebox.showinfo("Mitigation complete", "No high-threat processes were found.")

if __name__ == "__main__":
    root = tk.Tk()
    app = KeyShieldGUI(root)
    root.mainloop()
