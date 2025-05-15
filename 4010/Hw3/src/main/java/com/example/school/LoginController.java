package com.example.school;

import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class LoginController {
	private final JwtService jwtService;
	private final AuthenticationManager authenticationManager;

	public LoginController(JwtService jwtService, AuthenticationManager authenticationManager) {
		this.jwtService = jwtService;
		this.authenticationManager = authenticationManager;
	}

	@PostMapping("/login")
	public ResponseEntity<?> getToken(@RequestBody AccountCredentials credentials) {
		UsernamePasswordAuthenticationToken creds = new UsernamePasswordAuthenticationToken(credentials.username(),
				credentials.password()); // obtain {username, password} from login page
		// check if user exists in database
		// this authentication process is performed by loadUserByUsername() in UserDetailsServiceImpl
		// if user does not exist in database, a "Bad credentials" exception will be thrown
		// and will not proceed to the next line
		Authentication auth = authenticationManager.authenticate(creds);
		// Generate JWT token if login user exists in database
		String jwts = jwtService.getToken(auth.getName());
		// Build response with the generated token
		return ResponseEntity.ok().header(HttpHeaders.AUTHORIZATION, "Bearer" + jwts)
				.header(HttpHeaders.ACCESS_CONTROL_EXPOSE_HEADERS, "Authorization").build();
	}
}