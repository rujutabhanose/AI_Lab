package chatbot;
import java.io.File;
import org.alicebot.ab.*;
import org.alicebot.ab.utils.IOUtils;

public class ChatBot {

    private static final boolean TRACE_MODE = false;
    static String botName = "super";
 
    public static void main(String[] args) {
        try {
 
            String resourcesPath = getResourcesPath();
            System.out.println(resourcesPath);
            System.out.println("AIML Path: " + resourcesPath + "/bots/super/aiml");
            MagicBooleans.trace_mode = TRACE_MODE;
            Bot bot = new Bot("super", resourcesPath);
            bot.writeAIMLFiles();
            Chat chatSession = new Chat(bot);
            String textLine = "";
 
            while(true) {
                System.out.print("Human : ");
                textLine = IOUtils.readInputTextLine();
                if ((textLine == null) || (textLine.length() < 1))
                    textLine = MagicStrings.null_input;
                else {
                    String request = textLine;
                    String response = chatSession.multisentenceRespond(request);
                    System.out.println("Robot : " + response);
                    if(request.toLowerCase().equals("bye"))
                        System.exit(0);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
 
    private static String getResourcesPath() {
        File currDir = new File("..");
        String path = currDir.getAbsolutePath();
        return path;
    }
}