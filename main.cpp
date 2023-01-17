struct msg
{
    std::string message;
    std::string author;
    std::string timestamp;
}; //Already defined in KeyAuth.hpp, its here only for demonstration

std::vector<msg> MainMessages = KeyAuthApp.chatget("main"); //return a std::vector of the 'main' channel messages with the struct msg
KeyAuthApp.chatsend(MessageText, "main");// send a message to the 'main' channel, MessageText is a std::string

std::vector<msg> ChatMessages;
void Messages()
{
    while (true)
    {
        if (loggedin)
        {
            ChatMessages = KeyAuthApp.chatget(XorStr("general"));
            Sleep(1000);
        }
    }
}

new std::thread(Messages);

for (KeyAuth::msg message : ChatMessages)
{
    std::string colon = ":";
    std::string msg = message.author.c_str() + colon + message.message.c_str();
    ImGui::Text(msg.c_str());
}

static char input[256] = "";

ImGui::InputText("", input, 256); ImGui::SameLine();

if (ImGui::Button(XorStr("Send").c_str(), ImVec2(50, 26))) 
{
   KeyAuthApp.chatsend(input, XorStr("general").c_str());
   ChatMessages = KeyAuthApp.chatget(XorStr("general").c_str());
   memset(input, 0, sizeof input);
} //frags helped me with this 
