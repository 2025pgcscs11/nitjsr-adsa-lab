/* JEEMainGUIInterface.java
   Single-file Java Swing application for JEES (desktop GUI).
   Compile: javac JEEMainGUIInterface.java
   Run:     java JEEMainGUIInterface
*/

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.io.*;
import java.util.*;
import java.util.List;

class Student implements Comparable<Student> {
    String roll; // 6 chars
    String name;
    String category; // "Gen" or "Resrv"
    int math, phy, chem; // -1 means not yet filled

    Student(String roll, String name, String category, int math, int phy, int chem) {
        this.roll = roll; this.name = name; this.category = category;
        this.math = math; this.phy = phy; this.chem = chem;
    }

    /**
     * Return total marks or -1 if any mark is missing.
     */
    int total() {
        return (math < 0 || phy < 0 || chem < 0) ? -1 : (math + phy + chem);
    }

    // For sorting merit: higher total first; tie -> higher math; tie -> higher phy; tie -> roll ascending
    @Override
    public int compareTo(Student other) {
        int t1 = this.total(), t2 = other.total();
        if (t1 != t2) return Integer.compare(t2, t1); // higher total first
        if (this.math != other.math) return Integer.compare(other.math, this.math);
        if (this.phy != other.phy) return Integer.compare(other.phy, this.phy);
        return this.roll.compareTo(other.roll);
    }

    String toCSV() {
        // roll,name,category,math,phy,chem
        return roll + "," + escape(name) + "," + category + "," + math + "," + phy + "," + chem;
    }

    /**
     * Parse a CSV line into Student. Returns null for header or malformed lines.
     * Expects at least 6 comma-separated fields. Name escaping uses "&#44;" for commas.
     */
    static Student fromCSV(String line) {
        if (line == null) return null;
        line = line.trim();
        if (line.isEmpty()) return null;
        String lower = line.toLowerCase();
        // Skip header lines that start with "roll," or common header patterns
        if (lower.startsWith("roll,") || lower.contains("roll,name") || lower.startsWith("roll")) return null;

        // split to maximum 6 parts (roll, name, category, math, phy, chem)
        String[] parts = line.split(",", 6);
        if (parts.length < 6) return null;
        try {
            String roll = parts[0].trim();
            String name = unescape(parts[1].trim());
            String category = parts[2].trim();
            int math = Integer.parseInt(parts[3].trim());
            int phy  = Integer.parseInt(parts[4].trim());
            int chem = Integer.parseInt(parts[5].trim());
            return new Student(roll, name, category, math, phy, chem);
        } catch (NumberFormatException ex) {
            // malformed numeric field — skip this line
            return null;
        } catch (Exception ex) {
            return null;
        }
    }

    static String escape(String s) {
        return s.replace(",", "&#44;");
    }
    static String unescape(String s) {
        return s.replace("&#44;", ",");
    }
}

public class JEEMainGUIInterface extends JFrame {
    private Map<String, Student> students = new LinkedHashMap<>(); // roll -> student (preserve insertion order)
    private int nextSequence = 1; // used to generate roll numbers
    private final String DATAFILE = "students.csv";

    // GUI components
    private JTextField regNameField;
    private JComboBox<String> regCategoryBox;
    private JLabel regRollLabel;

    private JTextField staffRollField, staffMathField, staffPhyField, staffChemField;
    private JButton staffUpdateButton;

    private JTextField studentRollField;
    private JTextArea studentResultArea;

    private JTable meritTable;
    private DefaultTableModel meritModel;

    public JEEMainGUIInterface() {
        super("JEEMainGUIInterface - JEE Exam System");
        loadData();
        buildUI();
        setSize(900, 650);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    private void buildUI() {
        JTabbedPane tabs = new JTabbedPane();

        // ---- Register tab ----
        JPanel regPanel = new JPanel(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.insets = new Insets(6,6,6,6);
        c.gridx = 0; c.gridy = 0; regPanel.add(new JLabel("Name:"), c);
        regNameField = new JTextField(25);
        c.gridx = 1; regPanel.add(regNameField, c);
        c.gridx = 0; c.gridy = 1; regPanel.add(new JLabel("Category:"), c);
        regCategoryBox = new JComboBox<>(new String[]{"Gen","Resrv"});
        c.gridx = 1; regPanel.add(regCategoryBox, c);
        c.gridx = 0; c.gridy = 2; regPanel.add(new JLabel("Assigned Roll:"), c);
        regRollLabel = new JLabel("(will appear after clicking Register)");
        c.gridx = 1; regPanel.add(regRollLabel, c);
        JButton regButton = new JButton("Register");
        c.gridx = 1; c.gridy = 3; regPanel.add(regButton, c);
        regButton.addActionListener(e -> registerAction());
        tabs.addTab("Register", regPanel);

        // ---- Staff tab ----
        JPanel staffPanel = new JPanel(new GridBagLayout());
        c.gridx = 0; c.gridy = 0; staffPanel.add(new JLabel("Roll No:"), c);
        staffRollField = new JTextField(10); c.gridx = 1; staffPanel.add(staffRollField, c);
        c.gridx = 0; c.gridy = 1; staffPanel.add(new JLabel("Math:"), c);
        staffMathField = new JTextField(5); c.gridx = 1; staffPanel.add(staffMathField, c);
        c.gridx = 0; c.gridy = 2; staffPanel.add(new JLabel("Physics:"), c);
        staffPhyField = new JTextField(5); c.gridx = 1; staffPanel.add(staffPhyField, c);
        c.gridx = 0; c.gridy = 3; staffPanel.add(new JLabel("Chemistry:"), c);
        staffChemField = new JTextField(5); c.gridx = 1; staffPanel.add(staffChemField, c);
        staffUpdateButton = new JButton("Update Marks");
        c.gridx = 1; c.gridy = 4; staffPanel.add(staffUpdateButton, c);
        staffUpdateButton.addActionListener(e -> staffUpdateAction());
        tabs.addTab("Staff: Enter Marks", staffPanel);

        // ---- Student tab ----
        JPanel studentPanel = new JPanel(new BorderLayout());
        JPanel top = new JPanel();
        top.add(new JLabel("Enter Roll No:"));
        studentRollField = new JTextField(8);
        top.add(studentRollField);
        JButton viewBtn = new JButton("View Result");
        top.add(viewBtn);
        viewBtn.addActionListener(e -> viewResultAction());
        studentPanel.add(top, BorderLayout.NORTH);
        studentResultArea = new JTextArea();
        studentResultArea.setEditable(false);
        studentResultArea.setFont(new Font("Monospaced", Font.PLAIN, 12));
        studentPanel.add(new JScrollPane(studentResultArea), BorderLayout.CENTER);
        tabs.addTab("Student: View Result", studentPanel);

        // ---- Merit List tab ----
        JPanel meritPanel = new JPanel(new BorderLayout());
        meritModel = new DefaultTableModel(new Object[]{"Rank","Roll","Name","Category","Math","Phy","Chem","Total"},0) {
            @Override public boolean isCellEditable(int r,int c){return false;}
        };
        meritTable = new JTable(meritModel);
        meritTable.setAutoCreateRowSorter(true);
        meritPanel.add(new JScrollPane(meritTable), BorderLayout.CENTER);
        JButton refreshMeritBtn = new JButton("Refresh Merit List");
        refreshMeritBtn.addActionListener(e -> refreshMeritList());
        meritPanel.add(refreshMeritBtn, BorderLayout.SOUTH);
        tabs.addTab("Merit List", meritPanel);

        add(tabs);
    }

    private void registerAction() {
        String name = regNameField.getText().trim();
        String category = (String) regCategoryBox.getSelectedItem();
        if (name.isEmpty()) { JOptionPane.showMessageDialog(this, "Name required"); return; }
        String roll = generateRoll(category);
        Student s = new Student(roll, name, category, -1, -1, -1);
        students.put(roll, s);
        saveData();
        regRollLabel.setText(roll);
        JOptionPane.showMessageDialog(this, "Registered. Roll: " + roll);
        regNameField.setText("");
    }

    private void staffUpdateAction() {
        String roll = staffRollField.getText().trim();
        if (!students.containsKey(roll)) { JOptionPane.showMessageDialog(this, "Roll not found"); return; }
        try {
            int m = Integer.parseInt(staffMathField.getText().trim());
            int p = Integer.parseInt(staffPhyField.getText().trim());
            int c = Integer.parseInt(staffChemField.getText().trim());
            if (!validMark(m) || !validMark(p) || !validMark(c)) {
                JOptionPane.showMessageDialog(this, "Marks must be 0..200 (or set range as you need)");
                return;
            }
            Student s = students.get(roll);
            s.math = m; s.phy = p; s.chem = c;
            saveData();
            JOptionPane.showMessageDialog(this, "Marks updated for " + roll);
            staffRollField.setText(""); staffMathField.setText(""); staffPhyField.setText(""); staffChemField.setText("");
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Enter numeric marks");
        }
    }

    private void viewResultAction() {
        String roll = studentRollField.getText().trim();
        if (!students.containsKey(roll)) { studentResultArea.setText("Roll not found."); return; }
        Student s = students.get(roll);
        StringBuilder sb = new StringBuilder();
        sb.append("Roll: ").append(s.roll).append("\n");
        sb.append("Name: ").append(s.name).append("\n");
        sb.append("Category: ").append(s.category).append("\n");
        if (s.total() < 0) sb.append("Marks not yet entered by office staff.\n");
        else {
            sb.append("Math: ").append(s.math).append("\n");
            sb.append("Physics: ").append(s.phy).append("\n");
            sb.append("Chemistry: ").append(s.chem).append("\n");
            sb.append("Total: ").append(s.total()).append("\n");
            // compute rank (merit serial)
            List<Student> ranked = new ArrayList<>(students.values());
            ranked.removeIf(st -> st.total() < 0);
            Collections.sort(ranked);
            int rank = 1;
            for (Student st : ranked) {
                if (st.roll.equals(s.roll)) { sb.append("Merit Serial: ").append(rank).append("\n"); break; }
                rank++;
            }
        }
        studentResultArea.setText(sb.toString());
    }

    private void refreshMeritList() {
        List<Student> r = new ArrayList<>(students.values());
        r.removeIf(st -> st.total() < 0); // only those with all marks entered
        Collections.sort(r);
        meritModel.setRowCount(0);
        int rk = 1;
        for (Student s : r) {
            meritModel.addRow(new Object[]{rk++, s.roll, s.name, s.category, s.math, s.phy, s.chem, s.total()});
        }
    }

    private boolean validMark(int x) {
        return x >= 0 && x <= 200; // adjust max as per your marking scheme
    }

    // Roll number generation: 6 chars. Format: [G|R][00001..]
    private String generateRoll(String category) {
        if (nextSequence == 1) computeNextSequenceFromData();
        String prefix = category.equals("Gen") ? "G" : "R";
        String roll = String.format("%s%05d", prefix, nextSequence++);
        return roll;
    }

    private void computeNextSequenceFromData() {
        int maxSeq = 0;
        for (String r : students.keySet()) {
            if (r.length() >= 6) {
                String body = r.substring(1);
                try {
                    int seq = Integer.parseInt(body);
                    if (seq > maxSeq) maxSeq = seq;
                } catch (Exception e) {}
            }
        }
        nextSequence = maxSeq + 1;
    }

    // Persistence: CSV (robust loading that skips header/bad lines)
    private void loadData() {
        File f = new File(DATAFILE);
        if (!f.exists()) return;
        try (BufferedReader br = new BufferedReader(new FileReader(f))) {
            String line;
            int lineno = 0;
            while ((line = br.readLine()) != null) {
                lineno++;
                Student s = Student.fromCSV(line);
                if (s != null) students.put(s.roll, s);
                // else skip header or malformed line silently
            }
            computeNextSequenceFromData();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Error loading data: " + e.getMessage());
        }
    }

    private void saveData() {
        try (PrintWriter pw = new PrintWriter(new FileWriter(DATAFILE))) {
            // optional header for readability
            pw.println("Roll,Name,Category,Math,Physics,Chemistry");
            for (Student s : students.values()) pw.println(s.toCSV());
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Error saving data: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new JEEMainGUIInterface().setVisible(true));
    }
}
