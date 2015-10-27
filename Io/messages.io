postOffice := Object clone
postOffice packageSender := method(call sender)
postOffice messageTarget := method(call target)
postOffice messageArgs := method(call message arguments)
postOffice messageName := method(call message name)

mailer := Object clone
mailer deliver := method(postOffice packageSender)

mailer deliver println
postOffice messageTarget println
postOffice messageArgs("one", 2, :three) println
postOffice messageName println
