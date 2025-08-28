 
 # ==== Methods ====
 def user_url(username = session[:username])
  return "no_identity" if not username or username == ""
   "#{base_url}#{SERVER_CONF[:prefix]}#{username}"
 end
 
   return session[:approvals].member?(trust_root)
 end
 
def is_authorized(identity_url, trust_root, username = session[:username])
  return (username and (identity_url == user_url(username)) and approved(trust_root))
 end
 
 def openid
   else
     session[:approvals] = [oidreq.trust_root]
   end
  if is_authorized(identity, oidreq.trust_root, username)
    oidresp = oidreq.answer(true, nil, identity)
    add_sreg(oidreq, oidresp, userinfo)
    add_pape(oidreq, oidresp)
  else
    session[:username] = nil
    session[:approvals] = []
    oidresp = oidreq.answer(false)
  end
   return render_response(oidresp)
 end
 