import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class CalculatorButtonsPanel extends JPanel {
    private List<CalculatorButtons> buttons;
    CalculatorButtonsPanel(){
        this.buttons = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            CalculatorButtons numbers = new CalculatorButtons(String.valueOf(i));
            numbers.setFont(new Font("Arial", Font.PLAIN, 20));
            this.buttons.add(numbers);
        }
        CalculatorButtons btn = new CalculatorButtons("AC");
        this.buttons.add(btn);
        CalculatorButtons btn1 = new CalculatorButtons("C");
        this.buttons.add(btn1);
        CalculatorButtons btn2 = new CalculatorButtons("+/-");
        this.buttons.add(btn2);
        CalculatorButtons btn3 = new CalculatorButtons("/");
        this.buttons.add(btn3);
        CalculatorButtons btn4 = new CalculatorButtons("*");
        this.buttons.add(btn4);
        CalculatorButtons btn5 = new CalculatorButtons("+");
        this.buttons.add(btn5);
        CalculatorButtons btn6 = new CalculatorButtons("-");
        this.buttons.add(btn6);
        CalculatorButtons btn7 = new CalculatorButtons("=");
        this.buttons.add(btn7);
        CalculatorButtons btn8 = new CalculatorButtons("^");
        this.buttons.add(btn8);
        CalculatorButtons btn9 = new CalculatorButtons("%");
        this.buttons.add(btn9);
        btn.setFont(new Font("Arial", Font.PLAIN, 20));
        btn1.setFont(new Font("Arial", Font.PLAIN, 20));
        btn2.setFont(new Font("Arial", Font.PLAIN, 20));
        btn3.setFont(new Font("Arial", Font.PLAIN, 20));
        btn4.setFont(new Font("Arial", Font.PLAIN, 20));
        btn5.setFont(new Font("Arial", Font.PLAIN, 20));
        btn6.setFont(new Font("Arial", Font.PLAIN, 20));
        btn7.setFont(new Font("Arial", Font.PLAIN, 20));
        btn8.setFont(new Font("Arial", Font.PLAIN, 20));
        btn9.setFont(new Font("Arial", Font.PLAIN, 20));
        this.setLayout(new GridLayout(0,4));
        this.add(btn);
        this.add(btn1);
        this.add(btn9);
        this.add(btn3);
        this.add(this.buttons.get(7));
        this.add(this.buttons.get(8));
        this.add(this.buttons.get(9));
        this.add(btn4);
        this.add(this.buttons.get(4));
        this.add(this.buttons.get(5));
        this.add(this.buttons.get(6));
        this.add(btn6);
        this.add(this.buttons.get(1));
        this.add(this.buttons.get(2));
        this.add(this.buttons.get(3));
        this.add(btn5);
        this.add(this.buttons.get(0));
        this.add(btn8);
        this.add(btn7);
        this.add(btn2);
    }

    public List<CalculatorButtons> getButtons() {
        return buttons;
    }
}
