# typed: false
 class Backoffice::MessageController::MessageService
   extend T::Sig
 
     end
 
     if message.blank?
      @errors.push("#{I18n.t("layout.text.backoffice.management.users.send_email.message")}
                    #{I18n.t("errors.messages.blank")}")
     end
     if !message.blank? && message.length < 2
      @errors.push(I18n.t "errors.messages.message_min_length", min_length: 2)
     end
     if from_email == to_email
       @errors.push(I18n.t "errors.messages.recipient.same_as_user")
     end
     if to_email.blank?
      @errors.push("#{I18n.t("layout.text.backoffice.management.users.send_email.recipient")}
                    #{I18n.t("errors.messages.blank")}")
     end
     if @errors.any?
       @message_sent[:message] = @errors.join("\n")
     begin
       simulate_error?
 
      AdminMailer.send_message_to(from_name, from_email, to_name, to_email, message).deliver_now
 
       @message_sent[:success] = true
      @message_sent[:message] = I18n.t "layout.message.text.success_to_send"
     rescue Exception => e
       Rails.logger.error "Error to send message: #{e}"
      @message_sent[:message] = I18n.t "layout.message.text.error_to_send"
     ensure
       return @message_sent
     end
   sig { void }
   def self.simulate_error?
     raise_error = [1..10].sample % 2 == 0
    Rails.logger.debug "Should raise an error? #{raise_error ? "yes" : "no"}"
     if raise_error
       raise "Email could not be sent, check the logs for more details!"
     end