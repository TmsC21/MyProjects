import lombok.Data;

import javax.swing.*;
import java.awt.*;

@Data
public class MyFrame extends JFrame {
    MyButton convertButton;
    MyButton resetButton;
    JTextArea textArea;
    JTextArea convertedTextArea;
    MyFrame(){
        super("Payload factory");
        this.convertButton = new MyButton("Convert");
        this.resetButton = new MyButton("Reset");
        this.textArea = new JTextArea(150,50);
        this.convertedTextArea = new JTextArea(300,50);
        this.textArea.setSize(new Dimension(690,500));
        this.convertedTextArea.setSize(new Dimension(690,500));
        this.convertedTextArea.setEditable(false);
        JScrollPane scrollPaneTextArea = new JScrollPane(textArea,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        JScrollPane scrollPaneConvertedTextArea = new JScrollPane(convertedTextArea,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        this.add(scrollPaneTextArea , BorderLayout.WEST);
        this.add(scrollPaneConvertedTextArea ,BorderLayout.EAST);
        JPanel panel = new JPanel();
        panel.add(convertButton,BorderLayout.WEST);
        panel.add(resetButton,BorderLayout.EAST);
        this.add(panel,BorderLayout.PAGE_END);
        setDefaultCloseOperation(this.EXIT_ON_CLOSE);
        this.setSize(1200,800);
        this.setVisible(true);
    }
}
