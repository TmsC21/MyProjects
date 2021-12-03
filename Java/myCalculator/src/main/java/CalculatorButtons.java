import javax.swing.*;

public class CalculatorButtons extends JButton {
    private String value;
    public CalculatorButtons(String value){
        super(value);
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
