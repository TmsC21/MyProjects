import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.List;

public class CalculatorController implements KeyListener, ActionListener {
    CalculatorFrame calculatorFrame;
    List<CalculatorButtons> calculatorButtons;
    double prewiousNumber;
    String function = "";
    CalculatorController(){
        this.calculatorFrame = new CalculatorFrame();
        this.calculatorButtons = this.calculatorFrame.buttonsPanel.getButtons();
        for (var btn: this.calculatorButtons) {
            btn.addActionListener(this);
        }
    }
    @Override
    public void keyTyped(KeyEvent e) {

    }
    @Override
    public void keyPressed(KeyEvent e) {

    }
    @Override
    public void keyReleased(KeyEvent e) {

    }
    @Override
    public void actionPerformed(ActionEvent e) {
        Object obj = e.getSource();
        for (var btns: this.calculatorButtons) {
            if(obj.equals(btns)){
                switch (btns.getValue()){
                    case "AC":
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("0");
                        prewiousNumber = 0;
                        function = "";
                        break;
                    case "C":
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            prewiousNumber = Long.parseLong(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("0");
                        break;
                    case "+/-":
                        int number = 0;
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            number = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        if(number < 0){
                            number = Math.abs(number);
                        }else if(number > 0){
                            number = -number;
                        }
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText(String.valueOf(number));
                        break;
                    case "/":
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            prewiousNumber = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        function = btns.getValue();
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("/");
                        break;
                    case "*":
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            prewiousNumber = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        function = btns.getValue();
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("*");
                        break;
                    case "+":
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            prewiousNumber = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        function = btns.getValue();
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("+");
                        break;
                    case "-":
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            prewiousNumber = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        function = btns.getValue();
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("-");
                        break;
                    case "=":
                        double result = 0;
                        int currentNumber;
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            currentNumber = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }else{
                            break;
                        }
                        switch (function) {
                            case "*":
                                result = prewiousNumber * currentNumber;
                                break;
                            case "/":
                                result = prewiousNumber / currentNumber;
                                break;
                            case "+":
                                result = prewiousNumber + currentNumber;
                                break;
                            case "-":
                                result = prewiousNumber - currentNumber;
                                break;
                            case "^":
                                result = Math.pow(prewiousNumber,currentNumber);
                                break;
                            case "%":
                                result = prewiousNumber % currentNumber;
                                break;
                        }
                        function = btns.getValue();
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText(String.valueOf((int)result));
                        break;
                    case "^":
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            prewiousNumber = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        function = btns.getValue();
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("^");
                        break;
                    case "%":
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            prewiousNumber = Integer.parseInt(this.calculatorFrame.calculatorDisplay.getDisplay().getText());
                        }
                        function = btns.getValue();
                        this.calculatorFrame.calculatorDisplay.getDisplay().setText("%");
                        break;
                    default:
                        String num = "";
                        if(isNumeric(this.calculatorFrame.calculatorDisplay.getDisplay().getText())){
                            num = this.calculatorFrame.calculatorDisplay.getDisplay().getText();
                            if(num.equals("0")){
                                num = "";
                            }
                        }
                        if(function.equals("=")){
                            this.calculatorFrame.calculatorDisplay.getDisplay().setText(btns.getValue());
                            function = "";
                        }else{
                            this.calculatorFrame.calculatorDisplay.getDisplay().setText(num+btns.getValue());
                        }
                }
            }
        }
    }
    public static boolean isNumeric(String strNum) {
        try {
            double d = Double.parseDouble(strNum);
        } catch (NumberFormatException nfe) {
            return false;
        }
        return true;
    }
}
