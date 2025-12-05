
//// Cách này tốt hơn vì hook vào CreateMove function
//
///*
//void __fastcall hkCreateMove(void* thisptr, void* edx, int sequence_number, 
//                              float input_sample_frametime, bool active)
//{
//    // Gọi hàm gốc
//    oCreateMove(thisptr, edx, sequence_number, input_sample_frametime, active);
//    
//    // Lấy UserCmd
//    CUserCmd* cmd = GetUserCmd(sequence_number);
//    if (!cmd) return;
//    
//    // Lưu góc nhìn gốc
//    Vector3 originalViewAngles = cmd->viewangles;
//    
//    // Nếu có target và đang bắn
//    if (hasTarget && (cmd->buttons & IN_ATTACK))
//    {
//        // Set góc aim trong UserCmd
//        cmd->viewangles = bestAngle;
//        
//        // Chuẩn hóa góc
//        NormalizeAngles(cmd->viewangles);
//        ClampAngles(cmd->viewangles);
//    }
//    
//    // QUAN TRỌNG: Không restore viewAngles trong CreateMove
//    // Game sẽ tự động dùng cmd->viewangles để bắn
//    // nhưng screen viewAngles vẫn giữ nguyên
//}
//*/