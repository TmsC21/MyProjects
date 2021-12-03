import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class Controller implements ActionListener {
    MyFrame frame;
    Controller(){
        frame = new MyFrame();
        frame.getResetButton().addActionListener(this);
        frame.getConvertButton().addActionListener(this);
    }
    ArrayList<String> convertWord;
    @Override
    public void actionPerformed(ActionEvent e) {
        convertWord = new ArrayList<>();
        if(e.getSource() == frame.getConvertButton()){
            for (String line : frame.getTextArea().getText().split("\\n")){
                String[] wordsWithSpace = line.split("\\s+");
                if(wordsWithSpace.length > 2){
                    findKeyValue(wordsWithSpace,convertWord);
                }
            }
            frame.getConvertedTextArea().append("<payloadFactory media-type=\"json\">\n");
            frame.getConvertedTextArea().append("\t<format>\n\t\t{\n");
            int x = 1;
            for (int i = 0; i < convertWord.size(); i++) {
                String[] tmp = convertWord.get(i).split("=");
                if(i == convertWord.size()-1){
                    if(tmp[1].equals("Integer")){
                        frame.getConvertedTextArea().append("\t\t\t\""+tmp[0]+"\""+": $"+x+"\n");
                    }else{
                        frame.getConvertedTextArea().append("\t\t\t\""+tmp[0]+"\""+": \"$"+x+"\"\n");
                    }
                }else{
                    if(tmp[1].equals("Integer")){
                        frame.getConvertedTextArea().append("\t\t\t\""+tmp[0]+"\""+": $"+x+",\n");
                    }else{
                        frame.getConvertedTextArea().append("\t\t\t\""+tmp[0]+"\""+": \"$"+x+"\",\n");
                    }
                }
                x++;
            }
            frame.getConvertedTextArea().append("\t\t}\n");
            frame.getConvertedTextArea().append("\t</format>\n\t<args>\n");
            for (int i = 0; i < x-1; i++) {
                String[] tmp = convertWord.get(i).split("=");
                if(tmp[1].equals("Integer")){
                    frame.getConvertedTextArea().append("\t\t<arg evaluator=\"xml\" expression=\"$ctx:INTEGER_VALUE_OF_"+tmp[0].toUpperCase()+"\"/>\n");
                }else{
                    frame.getConvertedTextArea().append("\t\t<arg evaluator=\"xml\" expression=\"$ctx:STRING_VALUE_OF_"+tmp[0].toUpperCase()+"\"/>\n");
                }
            }
            frame.getConvertedTextArea().append("\t</args>\n");
            frame.getConvertedTextArea().append("</payloadFactory>");
        }
        if(e.getSource() == frame.getResetButton()){
            this.frame.getTextArea().setText("");
            this.frame.getConvertedTextArea().setText("");
        }
    }
    private void findKeyValue(String[] words,ArrayList<String> hashMap){
        for (int x = 0; x < words.length; x++) {
            if(words[x].equals("String") || words[x].equals("Integer")){
                hashMap.add(words[x-1]+"="+words[x]);
                return;
            }
        }
    }
}

